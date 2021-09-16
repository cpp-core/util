// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/standard.h"

template<class T>
void to_sbs(std::ostream& os, const std::vector<T>& vec) {
    to_sbs(os, vec.size());
    for (const auto& element : vec)
	to_sbs(os, element);
}

template<class T>
void from_sbs(std::istream& is, std::vector<T>& vec) {
    size_t count;
    from_sbs(is, count);
    vec.resize(count);
    for (auto& element : vec)
	from_sbs(is, element);
}

