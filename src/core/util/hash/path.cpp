// Copyright (C) 2021, 2022 by Mark Melton
//

#include "core/util/hash/path.h"
#include "core/util/hash/combine.h"
#include "core/util/exception.h"
#include <filesystem>

namespace core::hasher
{

namespace fs = std::filesystem;

std::uint64_t Hash<fs::path>::operator()(const fs::path& path) const {
    if (fs::exists(path)) {
	if (fs::is_directory(path)) {
	    std::uint64_t hid{0};
	    for(const auto& p: fs::directory_iterator(path))
		core::detail::combine(hid, this->operator()(p));
	    return hid;
	}
	else {
	    std::string name{fs::absolute(path)};
	    auto size = fs::file_size(path);
	    std::uint64_t tp = fs::last_write_time(path).time_since_epoch().count();
	
	    std::uint64_t hid{0};
	    core::detail::combine(hid, std::hash<decltype(name)>{}(name));
	    core::detail::combine(hid, std::hash<decltype(size)>{}(size));
	    core::detail::combine(hid, std::hash<decltype(tp)>{}(tp));
	    return hid;
	}
    }
    throw core::runtime_error("hash: path not found: {}", path.c_str());
};

}; // core::hasher
