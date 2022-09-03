// Copyright (C) 2017, 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

namespace core {

template<typename T>
struct type_traits
{ };

template<>
struct type_traits<string>
{ constexpr static char const *name = "string"; };

template<>
struct type_traits<int8>
{ constexpr static char const *name = "int8"; };

template<>
struct type_traits<int16>
{ constexpr static char const *name = "int16"; };

template<>
struct type_traits<int32>
{ constexpr static char const *name = "int32"; };

template<>
struct type_traits<int64>
{ constexpr static char const *name = "int64"; };

template<>
struct type_traits<uint8>
{ constexpr static char const *name = "uint8"; };

template<>
struct type_traits<uint16>
{ constexpr static char const *name = "uint16"; };

template<>
struct type_traits<uint32>
{ constexpr static char const *name = "uint32"; };

template<>
struct type_traits<uint64>
{ constexpr static char const *name = "uint64"; };

template<>
struct type_traits<real32>
{ constexpr static char const *name = "real32"; };

template<>
struct type_traits<real64>
{ constexpr static char const *name = "real64"; };

template<>
struct type_traits<real128>
{ constexpr static char const *name = "real128"; };

}; // end ns core
