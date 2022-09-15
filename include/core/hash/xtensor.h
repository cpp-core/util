// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <xtensor/xarray.hpp>
#include "core/hash/hash.h"
#include "core/hash/detail/mixer.h"

namespace core::hasher {

template<class T>
struct Hash<xt::xarray<T>> {
    std::uint64_t operator()(const xt::xarray<T>& data) const noexcept {
	std::uint64_t v{0};
	for (const auto& x : data)
	    combine(v, Hash<T>{}(x));
	return v;
    }
};

}; // core::hasher
