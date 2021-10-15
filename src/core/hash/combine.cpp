// Copyright (C) 2021 by Mark Melton
//

#include "core/hash/combine.h"

namespace core::detail
{

uint64 rotl(uint64 n, int i) {
    auto m = (std::numeric_limits<uint64>::digits - 1);
    uint64 c = i & m;
    return (n << c) | (n >> ((uint64{0} - c) & m));
}

void combine(uint64& seed, uint64 key) {
    seed = rotl(seed, 21) ^ key;
}

}; // core::detail
