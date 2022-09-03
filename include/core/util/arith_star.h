// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

template<class T>
T&& min_star(T&& value) { return std::forward<T>(value); }

template<class T, class U, class... Ts>
auto min_star(T&& value0, U&& value1, Ts&&... values) {
    return (value0 < value1) ?
	min_star(value0, std::forward<Ts>(values)...) :
	min_star(value1, std::forward<Ts>(values)...);
}

template<class T>
T&& max_star(T&& value) { return std::forward<T>(value); }

template<class T, class U, class... Ts>
auto max_star(T&& value0, U&& value1, Ts&&... values) {
    return (value0 > value1) ?
	max_star(value0, std::forward<Ts>(values)...) :
	max_star(value1, std::forward<Ts>(values)...);
}
