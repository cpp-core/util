// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <fmt/format.h>
#include "core/hash/hash.h"

namespace core {

// Cache - manage cached files.
class Cache {
public:
    // Construct a cache corresponding to the given arguments.
    template<class... Args>
    Cache(Args&&... args)
	: hid_(core::hash(std::forward<Args>(args)...))
	, sid_(fmt::format("{:0x}", hid_)) {
    }

    // Return the unique name of the cache.
    std::string name() const;
    
    // Return true if this cache exists.
    bool exists() const;

    // Return true if the given `file` for this cache exists.
    bool exists(const std::string& file) const;

    // Return the directory corresponding to this cache creating the
    // directory if it does not exists.
    std::string get() const;

    // Create the directory corresponding to this cache.
    void prepare() const;
    
    // Return the existence and the path for the given file.
    std::pair<bool, std::string> get(const std::string& file) const;
    
    // Return the path corresponding to the given `file` or throw an
    // exception if it does not exists.
    std::string get_or_throw(const std::string& file) const;

private:
    std::uint64_t hid_;
    std::string sid_;
};

}; // core

