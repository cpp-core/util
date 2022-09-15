// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <exception>
#include <fmt/format.h>
#include <string_view>

namespace core {

struct runtime_error : public std::runtime_error
{
    using Base = std::runtime_error;
    using Base::Base;
    template<class... Args>
    runtime_error(std::string_view spec, const Args&... args)
	: Base(fmt::format(fmt::runtime(spec), args...))
    { }
};

}; // end ns core
