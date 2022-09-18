// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <utility>
#include <iterator>

namespace core {

/// The RangeForPair template class allows a range-based-for-loop to
/// iterate over the elements delineated by a begin and end iterator
/// pair.
///
/// \verbatim embed:rst:leading-slashes
///
/// ```{code-block} cpp
/// std::vector<int> vec{1, 2, 3, 4};
/// auto b = vec.begin() + 1;
/// auto e = vec.end();
/// for (auto e : RangeforPair{b, e}) {
///    // iterates over 2, 3, 4
/// }
/// ```
///
/// \endverbatim
///
template<class P>
struct RangeForPair {
    using Pair = P;
    using Type = std::decay_t<Pair>;
    using iterator_type = typename Type::first_type;
    using value_type = typename std::iterator_traits<iterator_type>::value_type;
    
    // Construct the pair capturing a reference if possible or copying
    // if necessary.
    explicit RangeForPair(std::add_rvalue_reference_t<P> pair)
	: pair_(std::forward<P>(pair)) {
    }

    // Constrcut the pair from begin and end iterators.
    explicit RangeForPair(const auto& begin, const auto& end)
	: pair_(begin, end) {
    }

    // Return the beginn iterator.
    auto begin() const { return pair_.first; }

    // Return the end iterator.
    auto end() const { return pair_.second; }

    // Provide default comparisons.
    auto operator<=>(const RangeForPair&) const = default;
    
private:
    Pair pair_;
};

// If constructed with an r-value reference, copy the pair. Otherwise,
// the default guide will be used and the pair will be referenced.
template<class P> explicit RangeForPair(P&&) -> RangeForPair<P>;

// Construction from begin and end iterators.
template<class T, class U> explicit RangeForPair(const T&, const U&) ->
    RangeForPair<std::pair<T,U>>;

}; // core
