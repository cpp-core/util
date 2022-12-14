// Copyright (C) 2021, 2022 by Mark Melton
//

#include <filesystem>
#include <fmt/format.h>
#include "core/util/cache/cache.h"
#include "core/util/exception.h"

namespace core
{

namespace fs = std::filesystem;

std::string cache_root() {
    if (auto p = getenv("CACHE_ROOT"); p)
	return std::string{p};
    if (auto p = getenv("HOME"); p)
	return fmt::format("{}/cache", p);
    return fmt::format("/home/cache");
}

std::string Cache::name() const {
    return fmt::format("{}/{}/{}/{}", cache_root(), sid_[0], sid_[1], sid_);
}

bool Cache::exists() const {
    return fs::exists(name());
}

bool Cache::exists(const std::string& file) const {
    auto path = fmt::format("{}/{}", name(), file);
    return fs::exists(path);
}

std::string Cache::get() const {
    auto path = name();
    fs::create_directories(path);
    return path;
}
    
void Cache::prepare() const {
    get();
}
    
std::pair<bool, std::string> Cache::get(const std::string& file) const {
    auto path = fmt::format("{}/{}", name(), file);
    auto exists = fs::exists(path);
    return std::make_tuple(exists, path);
}
    
std::string Cache::get_or_throw(const std::string& file) const {
    auto [exists, path] = get(file);
    if (exists)
	return path;
    throw core::runtime_error("cache: file does not exist: {}", path);
}

}; // core
