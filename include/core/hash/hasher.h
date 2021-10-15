// Copyright (C) 2021 by Mark Melton
//

#include <deque>
#include "core/mp/same.h"
#include "core/hash/mixer.h"

namespace core::detail {

template<class T>
struct hasher;

template<class T>
requires std::is_pod_v<T>
struct hasher<T> {
    using U = std::decay_t<T>;
    size_t operator()(const T& value) const noexcept {
	return mixer(std::hash<U>{}(value), 32);
    }
};

template<class T>
requires core::mp::is_same_template_v<T, std::pair>
struct hasher<T> {
    size_t operator()(const T& value) const noexcept {
	size_t v{0};
	combine(v, hasher<typename T::first_type>{}(value.first));
	combine(v, hasher<typename T::second_type>{}(value.second));
	return v;
    }
};

template<class T>
requires (core::mp::is_same_template_v<T, std::vector> or
	  core::mp::is_same_template_v<T, std::list> or
	  core::mp::is_same_template_v<T, std::deque> or
	  core::mp::is_same_template_v<T, std::map> or
	  core::mp::is_same_template_v<T, std::set>)
struct hasher<T> {
    size_t operator()(const T& container) const noexcept {
	size_t v{0};
	for (const auto& element : container)
	    combine(v, hasher<std::decay_t<decltype(element)>>{}(element));
	return v;
    }
};

}; // core:detail
