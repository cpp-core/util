// Copyright (C) 2021, 2022 by Mark Melton
//

#include <limits>
#include "core/util/hash/combine.h"

namespace core::detail
{

std::uint64_t rotl(std::uint64_t n, int i) {
    auto m = (std::numeric_limits<std::uint64_t>::digits - 1);
    std::uint64_t c = i & m;
    return (n << c) | (n >> ((std::uint64_t{0} - c) & m));
}

void combine(std::uint64_t& seed, std::uint64_t key) {
    seed = rotl(seed, 21) ^ key;
}

}; // core::detail
