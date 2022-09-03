// Copyright (C) 2022 by Mark Melton
//

#pragma once
#include <utility>

namespace core {

// Template class RangeForZip captures the supplied `first` and
// `second` containers and adapts them for use with a
// range-based-for-loop return the zipped elements.
template<class T, class U>
struct RangeForZip {
    RangeForZip(std::add_rvalue_reference_t<T> first, std::add_rvalue_reference_t<U> second)
 	: first_(first)
	, second_(second) {
    }
    using first_type = std::decay_t<T>;
    using second_type = std::decay_t<U>;
    
    using first_iter_type = typename first_type::iterator;
    using second_iter_type = typename second_type::iterator;
    
    struct iterator_t {
	const RangeForZip& zip_; 
	first_iter_type first_iter;
	second_iter_type second_iter;

	auto operator*() {
	    return std::make_pair(*first_iter, *second_iter);
	}

	iterator_t& operator++() {
	    ++first_iter;
	    ++second_iter;
	    return *this;
	}
	
	bool done() const {
	    return first_iter == zip_.first_.end() and
		second_iter == zip_.second_.end();
	}
    };
    
    struct sentinel_t { };

    friend bool operator!=(iterator_t iter, sentinel_t) { return not iter.done(); }
    
    iterator_t begin() { return { *this, first_.begin(), second_.begin() }; }
    sentinel_t end() { return {}; }
    
    iterator_t cbegin() { return { *this, first_.begin(), second_.begin() }; }
    sentinel_t cend() const { return {}; }

private:
    T first_;
    U second_;
};

template<class T, class U> RangeForZip(T&, U&) -> RangeForZip<T&, U&>;

}; // core
