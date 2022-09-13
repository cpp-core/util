// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include "core/util/unsigned_real.h"

namespace core {
inline namespace util {
       
void unsigned_real::validate() {
    if (value < 0.0)
	throw core::runtime_error("unsigned_real has negative value: {}", value);
}

void to_json(json& j, unsigned_real value) {
    j = (double)value;
}

void from_json(const json& j, unsigned_real& value) {
    value = j.get<double>();
}

}; // util
}; // core
