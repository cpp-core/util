// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

template<template<class...> class C, class T, class U>
bool has_common_element(const C<T>& a, const C<U>& b)
{
    ExpectTRUE(std::is_sorted(a.begin(), a.end()));
    ExpectTRUE(std::is_sorted(b.begin(), b.end()));
    
    auto iter_a = a.begin();
    auto iter_b = b.begin();
    while (iter_a < a.end() and iter_b < b.end())
	if (*iter_a < *iter_b)
	    ++iter_a;
	else if (*iter_b < *iter_a)
	    ++iter_b;
	else
	    return true;
    return false;
}
