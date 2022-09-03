// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

namespace core {

// The RangeForEnum template class facilitate range-based-for-loop
// iteration over the values of an enumeration. The first enumerated
// values must have a corresponding integral value of zero, the last
// enumerated value must be called Sentinel and there cannot be any
// gaps.
//
// e.g `for (auto e : RangeForEnum<MyEnumClass>{});`
template<class T>
struct RangeForEnum {};

namespace detail {

template<class T>
struct RangeIterForEnum {
    RangeIterForEnum(T e): e_(e) {}
    RangeIterForEnum operator++() {
	e_ = static_cast<T>(static_cast<uint>(e_) + 1);
	return *this;
    }
    bool operator!=(const RangeIterForEnum<T>& other) const { return e_ != other.e_; }
    const T& operator*() const { return e_; }
private:
    T e_;
};

}; // detail

template<class T>
auto begin(RangeForEnum<T>) { return detail::RangeIterForEnum(static_cast<T>(0)); }

template<class T>
auto end(RangeForEnum<T>) { return detail::RangeIterForEnum(T::Sentinel); }

}; // core

