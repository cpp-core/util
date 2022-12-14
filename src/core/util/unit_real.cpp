// Copyright (C) 2022 by Mark Melton
//


#include <fmt/format.h>
#include <stdexcept>
#include "core/util/unit_real.h"

namespace core {
inline namespace util {
       
template<class T>
void unit_real<T>::validate() {
    if (value_ < 0.0 or value_ >= 1.0)
	throw std::runtime_error(fmt::format("unit_real out of range: {}", value_));
}

template class unit_real<float>;
template class unit_real<double>;

}; // util
}; // core
