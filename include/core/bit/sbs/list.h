// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/standard.h"

template<class T>
void to_sbs(std::ostream& os, const std::list<T>& lst) {
    to_sbs(os, lst.size());
    for (auto iter = lst.begin(); iter != lst.end(); ++iter)
	to_sbs(os, *iter);
}

template<class T>
void from_sbs(std::istream& is, std::list<T>& lst) {
    lst.clear();
    size_t count;
    from_sbs(is, count);
    for (auto i = 0; i < count; ++i) {
	T element;
	from_sbs(is, element);
	lst.push_back(element);
    }
}
