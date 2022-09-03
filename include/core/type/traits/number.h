// Copyright (C) 2017, 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

namespace core { namespace detail {

template<class T>
struct next_larger;

template<>
struct next_larger<int8>
{ using type = int16; };

template<>
struct next_larger<int16>
{ using type = int32; };

template<>
struct next_larger<int32>
{ using type = int64; };

template<>
struct next_larger<int64>
{ using type = int128; };

}; // end ns detail

template<class T>
using next_larger_t = typename detail::next_larger<T>::type;

namespace detail
{

template<class T>
struct next_larger_fp;

template<>
struct next_larger_fp<int16>
{ using type = real32; };

template<>
struct next_larger_fp<int32>
{ using type = real64; };

template<>
struct next_larger_fp<int64>
{ using type = real128; };

}; // end ns detail

template<class T>
using next_larger_fp_t = typename detail::next_larger_fp<T>::type;

}; // end ns core
