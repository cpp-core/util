// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

namespace core {

// Reverse the iteration in a range-based for loop.
//
// The RangeForReverse template class is used to reverse the iteration
// in a range-based for loop or other similar circumstance. It will
// store a reference to the container if possible or move from a
// temporary if necessary.
//
// *for (auto elem : RangeForReverse{elems});*
template<class C>
struct RangeForReverse {
    RangeForReverse(C&& c) : container_(std::forward<C>(c)) { }
    auto begin() { return container_.rbegin(); }
    auto end() { return container_.rend(); }
    auto cbegin() const { return container_.crbegin(); }
    auto cend() const { return container_.crend(); }
    C container_;
};

// If constructed with an l-value, store a reference to the container.
template<class C> RangeForReverse(C&) -> RangeForReverse<C&>;

}; // core

