// Copyright (C) 2021 by Mark Melton
//

#include "core/hash/path.h"
#include "core/hash/chrono.h"
#include "core/hash/combine.h"

namespace core::hasher
{

namespace fs = std::filesystem;

uint64 Hash<fs::path>::operator()(const fs::path& path) const {
    if (fs::exists(path)) {
	if (fs::is_directory(path)) {
	    uint64 hid{0};
	    for(const auto& p: fs::directory_iterator(path))
		core::detail::combine(hid, this->operator()(p));
	    return hid;
	}
	else {
	    auto n = fs::file_size(path);
	    auto tp = fs::last_write_time(path).time_since_epoch().count();
	
	    uint64 hid{0};
	    core::detail::combine(hid, std::hash<decltype(n)>{}(n));
	    core::detail::combine(hid, std::hash<decltype(tp)>{}(tp));
	    return hid;
	}
    }
    throw core::runtime_error("hash: path not found: {}", path.c_str());
};

}; // core::hasher
