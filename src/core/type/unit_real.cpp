// Copyright (C) 2022 by Mark Melton
//

#include "core/type/unit_real.h"

namespace core {
inline namespace type {
       
template<class T>
void unit_real<T>::validate() {
    if (value_ < 0.0 or value_ >= 1.0)
	throw core::runtime_error("unit_real out of range: {}", value_);
}

template class unit_real<float>;
template class unit_real<double>;

}; // type
}; // core
