// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/arith_star.h"

// splat - Return the specified vector elements as a tuple which can
// be unpacked using structered bindings.
//
// ints vec{0, 1, 2, 3, 4, 5, 6};
// auto [a, b] = splat(vec, 4, 5);
// a == 4 and b == 5
//
template<class T, class I, class... Is>
requires (std::is_integral_v<I> and std::conjunction_v<std::is_integral<Is>...>)
auto splat(const std::vector<T>& vec, I arg, Is... args) {
    auto mdx = max_star(arg, args...);
    if (mdx >= 0 and mdx < vec.size())
	return std::make_tuple(vec.at(arg), vec.at(args)...);
    throw core::runtime_error("splat index {} not less than vector size {}", mdx, vec.size());
}
