// Copyright (C) 2022 by Mark Melton
//

#pragma once
#include <cstdint>

namespace core {
inline namespace util {
       
// The **unit_real** template class models the concept of a
// real-valued quantity in the range [0,1). The goal is transparent
// interoperability with the standard `real` quantities.
template<class T>
class unit_real {
public:
    unit_real(T x = 0.0)
	: value_(x) {
	validate();
    }
    
    operator T() const { return value_; }

    // Return an **n** bit quantized representation of the underlying
    // real-valued quantity.
    std::uint64_t quantize(int n) const {
	return value_ * (1ul << n);
    }
    
private:
    void validate();
    T value_;
};

using unit_real32 = unit_real<float>;
using unit_real64 = unit_real<double>;

}; // type
}; // core

