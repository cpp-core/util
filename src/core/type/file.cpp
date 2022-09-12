// Copyright (C) 2021, 2022 by Mark Melton
//

#include <filesystem>
#include <fstream>
#include "core/util/file.h"
#include "core/codex/filter_comments.h"

namespace fs = std::filesystem;

namespace core
{

File::File(const std::string& str)
    : Base(str) {
}

File::File(std::string&& str)
    : Base(str) {
}
    
bool File::exists() const {
    return fs::exists(std::string{*this});
}

std::ofstream File::as_ofstream() const {
    std::ofstream ofs{*this};
    return ofs;
}

std::ifstream File::as_ifstream() const {
    std::ifstream ofs{*this};
    return ofs;
}

File::Compressor File::as_zstd_compressor() const {
    return Compressor{std::ofstream{*this}};
}
    
File::Decompressor File::as_zstd_decompressor() const {
    return Decompressor{std::ifstream{*this}};
}

std::optional<json> File::as_json() const {
    std::ifstream ifs{*this};
    if (not ifs.good())
	return std::nullopt;
    json j;
    core::filter_comments(ifs) >> j;
    return j;
}

void File::create_directories() const {
    fs::create_directories(fs::path{str()}.remove_filename());
}

void File::create(const json& j, bool verbose) const {
    create_directories();
    std::ofstream ofs{*this};
    if (not ofs.good())
	throw core::runtime_error("Failed to create file: {}", str());
    if (verbose) ofs << j.dump(4);
    else ofs << j;
}

}; // core
