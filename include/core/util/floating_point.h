// Copyright (C) 2023 by Mark Melton
//

#pragma once
#include <algorithm>
#include <bit>
#include <concepts>
#include <cmath>
#include <cfloat>

namespace core {

/// Return the pair (integer, base-2 exponent) corresponding to the
/// given floating point value. That is, return the pair (i, e) such
/// that i x 2^e == x.
template<std::floating_point T>
auto fp_to_integer_exponent(T x) {
    int exp{};
    auto r = std::frexp(x, &exp);
    uint64_t m = abs(r) * pow(2, DBL_MANT_DIG);
    exp -= DBL_MANT_DIG;

    auto norm_shift = std::max(0, std::min(-exp, std::countr_zero(m)));
    m >>= norm_shift;
    exp += norm_shift;

    int64_t n(m);
    n = r < 0 ? -n : +n;
    return std::make_pair(n, exp);
}

/// Return the floating point number corresponding to the given
/// integer raised to the base-2 exponent.
inline auto integer_exponent_to_fp(int64_t n, int exponent) {
    return std::ldexp((double)n, exponent);
}

}; // core
