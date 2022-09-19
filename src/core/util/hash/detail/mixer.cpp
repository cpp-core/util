// Copyright (C) 2021, 2022 by Mark Melton
//

#include "core/util/hash/detail/mixer.h"

namespace core::detail
{

std::uint64_t xorshift(const std::uint64_t& n, int i) {
    return n ^ (n >> i);
}

std::uint64_t mixer(std::uint64_t n, int b) {
    std::uint64_t p = 0x5555555555555555;
    std::uint64_t c = 17316035218449499591ull;
    return c * xorshift(p * xorshift(n, b), b);
}

}; // core::detail
