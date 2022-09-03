// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"
#include "core/extra/json/nljson.h"
#include "core/codex/zstd/compressor.h"
#include "core/codex/zstd/decompressor.h"

namespace core {

// File - Transparently extends std::string with file operations.
class File : public std::string {
public:
    using Base = std::string;
    using Base::Base;

    using Compressor = zstd::Compressor<std::ofstream>;
    using Decompressor = zstd::Decompressor<std::ifstream>;
    
    // Construct a File from std::string.
    File(const std::string& str);

    // Construct a File by moving from std::string.
    File(std::string&& str);
    
    // Return reference to the underlying string
    const std::string& str() const { return *this; }

    // Return true if the file exists, false otherwise.
    bool exists() const;

    // Return an std::ofstream handle to the file.
    std::ofstream as_ofstream() const;
    
    // Return an std::ifstream handle to the file.
    std::ifstream as_ifstream() const;

    // Return a compressor for the file.
    Compressor as_zstd_compressor() const;
    
    // Return a decompressor for the file.
    Decompressor as_zstd_decompressor() const;
    
    // Return the file contents interpreted as json.
    std::optional<json> as_json() const;

    // Create directories for the file.
    void create_directories() const;
	
    // Write `json` to newly created file.
    void create(const json& j, bool verbose = false) const;
private:
};

using Files = vector<File>;

}; // core
