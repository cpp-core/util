// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include <xtensor/xarray.hpp>
#include "core/hash/hash.h"
#include "core/hash/detail/mixer.h"

namespace core::hasher {

template<class T>
struct Hash<xt::xarray<T>> {
    uint64 operator()(const xt::xarray<T>& data) const noexcept {
	uint64 v{0};
	for (const auto& x : data)
	    combine(v, Hash<T>{}(x));
	return v;
    }
};

}; // core::hasher
