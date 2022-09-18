// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once

namespace core {

/// The RangeForEnum template class allows a range-based-for-loop to
/// iterate over the values of a conforming enumeration.
///
/// A conforming enumeration must satisfy the following:
///
/// - The first enumerated value must have a integral value of zero.
/// - The last enumerated value must be called `Sentinel`.
/// - There cannot be any gaps in the enumeration.
///
/// \verbatim embed:rst:leading-slashes
///
/// ```{code-block} cpp
/// enum class E { a, b, c, Sentinel };
/// for (auto e : RangeforEnum<E>{}) {
///    // iterates over a, b, c
/// }
/// ```
///
/// \endverbatim
///
template<class T>
struct RangeForEnum {};

namespace detail {

template<class T>
struct RangeIterForEnum {
    RangeIterForEnum(T e): e_(e) {}
    RangeIterForEnum operator++() {
	e_ = static_cast<T>(static_cast<unsigned int>(e_) + 1);
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

