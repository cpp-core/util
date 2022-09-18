// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/sbs/decl.h"

template<class T>
requires core::sbs::SequenceContainer<T>
void to_sbs(std::ostream& os, const T& container) {
    to_sbs(os, container.size());
    for (const auto& element : container)
	to_sbs(os, element);
}

template<class T>
requires core::sbs::SequenceContainer<T>
void from_sbs(std::istream& is, T& container) {
    size_t count;
    from_sbs(is, count);
    container.clear();
    for (auto i = 0; i < count; ++i) {
	typename T::value_type element;
	from_sbs(is, element);
	container.push_back(element);
    }
}

