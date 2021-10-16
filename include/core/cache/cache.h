// Copyright (C) 2021 by Mark Melton
//

#include "core/common.h"
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
    string name() const;
    
    // Return true if this cache exists.
    bool exists() const;

    // Return true if the given `file` for this cache exists.
    bool exists(const string& file) const;

    // Return the directory corresponding to this cache creating the
    // directory if it does not exists.
    string get() const;
    
    // Return the existence and the path for the given file.
    std::pair<bool, string> get(const string& file) const;
    
    // Return the path corresponding to the given `file` or throw an
    // exception if it does not exists.
    string get_or_throw(const string& file) const;

private:
    uint64 hid_;
    string sid_;
};

}; // core

