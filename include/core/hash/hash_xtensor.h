// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include <xtensor/xarray.hpp>
#include "core/hash/hash.h"

namespace core::detail {

template<class T>
struct hasher<xt::xarray<T>> {
    uint64 operator()(const xt::xarray<T>& data) const noexcept {
	uint64 v{0};
	for (const auto& x : data)
	    combine(v, hasher<T>{}(x));
	return v;
    }
};

}; // core:detail
