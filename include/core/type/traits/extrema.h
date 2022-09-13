// Copyright (C) 2017, 2018, 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <string>
#include <fmt/format.h>
#include "core/mp/same.h"
#include "core/mp/same.h"

namespace core
{

template<class T>
struct extrema;

template<>
struct extrema<bool>
{
    static bool min() { return false; }
    static bool max() { return true; }
    static std::string fmt_spec() { return "{}"; }
};

template<class T>
requires std::is_integral_v<T>
struct extrema<T> {
    static T min() { return std::numeric_limits<T>::min(); }
    static T max() { return std::numeric_limits<T>::max(); }
    static std::string fmt_spec() { return "{}"s; }
};

template<class T>
requires std::is_floating_point_v<T>
struct extrema<T> {
    static T min() { return - std::numeric_limits<T>::max(); }
    static T max() { return + std::numeric_limits<T>::max(); }
    static std::string fmt_spec()
    { return fmt::format("{{:.{}g}}", std::numeric_limits<T>::max_digits10); }
};

template<class T>
requires core::mp::is_same_template_v<T, std::pair>
struct extrema<T> {
    using FirstType = typename T::first_type;
    using SecondType = typename T::second_type;
    static T min() { return extrema<T>::min(); }
    static T max() { return extrema<T>::max(); }
};

}; // core
