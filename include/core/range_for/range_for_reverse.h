// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <utility>

namespace core {

/// The RangeForReverse template class allows a range-based-for-loop
/// to iterate over the values of a container in reverse order.
///
/// \verbatim embed:rst:leading-slashes
///
/// ```{code-block} cpp
/// std::vector<int> vec{1, 2, 3}
/// for (auto e : RangeforReverse{vec}) {
///    // iterates over 3, 2, 1
/// }
/// ```
///
/// \endverbatim
///
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

