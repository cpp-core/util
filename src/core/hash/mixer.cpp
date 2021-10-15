// Copyright (C) 2021 by Mark Melton
//

#include "core/hash/mixer.h"

namespace core::detail
{

uint64 xorshift(const uint64& n, int i) {
    return n ^ (n >> i);
}

uint64 mixer(uint64 n, int b) {
    uint64 p = 0x5555555555555555;
    uint64 c = 17316035218449499591ull;
    return c * xorshift(p * xorshift(n, b), b);
}

}; // core::detail
