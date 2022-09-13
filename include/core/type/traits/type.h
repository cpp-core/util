// Copyright (C) 2017, 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <string>
#include <cstdint>

namespace core {

template<typename T>
struct type_traits
{ };

template<>
struct type_traits<std::string>
{ constexpr static char const *name = "string"; };

template<>
struct type_traits<std::int8_t>
{ constexpr static char const *name = "int8"; };

template<>
struct type_traits<std::int16_t>
{ constexpr static char const *name = "int16"; };

template<>
struct type_traits<std::int32_t>
{ constexpr static char const *name = "int32"; };

template<>
struct type_traits<std::int64_t>
{ constexpr static char const *name = "int64"; };

template<>
struct type_traits<std::uint8_t>
{ constexpr static char const *name = "uint8"; };

template<>
struct type_traits<std::uint16_t>
{ constexpr static char const *name = "uint16"; };

template<>
struct type_traits<std::uint32_t>
{ constexpr static char const *name = "uint32"; };

template<>
struct type_traits<std::uint64_t>
{ constexpr static char const *name = "uint64"; };

template<>
struct type_traits<float>
{ constexpr static char const *name = "real32"; };

template<>
struct type_traits<double>
{ constexpr static char const *name = "real64"; };

template<>
struct type_traits<long double>
{ constexpr static char const *name = "real128"; };

}; // end ns core
