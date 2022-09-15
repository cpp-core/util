// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <filesystem>
#include "core/hash/hash.h"
#include "core/hash/detail/mixer.h"

namespace core::hasher {

template<>
struct Hash<std::filesystem::path> {
    std::uint64_t operator()(const std::filesystem::path& path) const;
};

}; // core::hasher
