// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <deque>
#include <list>
#include <map>
#include <set>
#include "core/mp/same.h"
#include "core/util/hash/hash.h"
#include "core/util/hash/detail/mixer.h"

namespace core::hasher {

using namespace core::detail;

template<class T>
requires (std::is_integral_v<T>
	  or std::is_floating_point_v<T>
	  or std::is_same_v<T, std::string>
	  or std::is_same_v<T, char const[]>
	  or std::is_same_v<T, const char *>
	  )
struct Hash<T> {
    using U = std::decay_t<T>;
    std::uint64_t operator()(const T& value) const noexcept {
	return mixer(std::hash<U>{}(value), 32);
    }
};

template<>
struct Hash<std::string> {
    std::uint64_t operator()(const std::string& s) const noexcept {
	return mixer(std::hash<std::string>{}(s), 32);
    }
};

template<class T>
requires core::mp::is_same_template_v<T, std::pair>
struct Hash<T> {
    std::uint64_t operator()(const T& value) const noexcept {
	std::uint64_t v{0};
	combine(v, Hash<typename T::first_type>{}(value.first));
	combine(v, Hash<typename T::second_type>{}(value.second));
	return v;
    }
};

template<class T>
requires (core::mp::is_same_template_v<T, std::vector> or
	  core::mp::is_same_template_v<T, std::list> or
	  core::mp::is_same_template_v<T, std::deque> or
	  core::mp::is_same_template_v<T, std::map> or
	  core::mp::is_same_template_v<T, std::set>)
struct Hash<T> {
    std::uint64_t operator()(const T& container) const noexcept {
	std::uint64_t v{0};
	for (const auto& element : container)
	    combine(v, Hash<std::decay_t<decltype(element)>>{}(element));
	return v;
    }
};

}; // core:hasher
