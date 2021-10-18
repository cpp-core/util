// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include <filesystem>
#include "core/hash/hash.h"
#include "core/hash/detail/mixer.h"

namespace core::hasher {

template<>
struct Hash<std::filesystem::path> {
    uint64 operator()(const std::filesystem::path& path) const;
};

}; // core::hasher
