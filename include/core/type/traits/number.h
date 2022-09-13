// Copyright (C) 2017, 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <cstdint>

namespace core { namespace detail {

template<class T>
struct next_larger;

template<>
struct next_larger<std::int8_t>
{ using type = std::int16_t; };

template<>
struct next_larger<std::int16_t>
{ using type = std::int32_t; };

template<>
struct next_larger<std::int32_t>
{ using type = std::int64_t; };

template<>
struct next_larger<std::int64_t>
{ using type = __int128; };

}; // end ns detail

template<class T>
using next_larger_t = typename detail::next_larger<T>::type;

namespace detail
{

template<class T>
struct next_larger_fp;

template<>
struct next_larger_fp<std::int16_t>
{ using type = float; };

template<>
struct next_larger_fp<std::int32_t>
{ using type = double; };

template<>
struct next_larger_fp<std::int64_t>
{ using type = long double; };

}; // end ns detail

template<class T>
using next_larger_fp_t = typename detail::next_larger_fp<T>::type;

}; // end ns core
