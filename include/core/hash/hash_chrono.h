// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/hash/hash.h"
#include "core/chrono.h"

namespace core::detail {

template<>
struct hasher<chron::Date> {
    uint64 operator()(const chron::Date& date) const noexcept {
	auto n = chron::sys_days(date).time_since_epoch().count();
	return mixer(std::hash<decltype(n)>{}(n), 32);
    }
};

template<class T>
requires core::mp::is_same_template_v<T, std::chrono::time_point>
struct hasher<T> {
    uint64 operator()(const T& tp) const noexcept {
	auto n = tp.time_since_epoch().count();
	return mixer(std::hash<decltype(n)>{}(n), 32);
    }
};

template<class T>
requires core::mp::is_same_template_v<T, std::chrono::duration>
struct hasher<T> {
    uint64 operator()(const T& duration) const noexcept {
	auto n = duration.count();
	return mixer(std::hash<decltype(n)>{}(n), 32);
    }
};

}; // core:detail
