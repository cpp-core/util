// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/chrono.h"
#include "core/hash/hash.h"
#include "core/hash/detail/mixer.h"
#include "core/mp/same.h"

namespace core::hasher {

template<>
struct Hash<chron::Date> {
    uint64 operator()(const chron::Date& date) const noexcept {
	auto n = chron::TimePoint{date}.time_since_epoch().count();
	return detail::mixer(std::hash<decltype(n)>{}(n), 32);
    }
};

template<>
struct Hash<chron::TimePoint> {
    uint64 operator()(const chron::TimePoint& tp) const noexcept {
	auto n = tp.time_since_epoch().count();
	return detail::mixer(std::hash<decltype(n)>{}(n), 32);
    }
};

template<class T>
requires chron::is_duration_v<T>
struct Hash<T> {
    uint64 operator()(const T& duration) const noexcept {
	auto n = duration.count();
	return detail::mixer(std::hash<decltype(n)>{}(n), 32);
    }
};

}; // core:hasher
