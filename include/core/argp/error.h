// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <typeinfo>
#include "core/common.h"
#include "core/demangle.h"

namespace core::argp
{

struct error : public std::runtime_error
{
    template<class... Args>
    error(string_view fmt, Args&&... args)
	: std::runtime_error(fmt::format(fmt, std::forward<Args>(args)...))
    { }
};

struct bad_type_error : public error
{
    bad_type_error(string_view arg_option_name, const std::type_info& arg_get_type,
		   const std::type_info& arg_option_type)
	: error("attempted to extract type '{}' from option '{}' which is actually of type '{}'.",
		core::demangle(arg_get_type.name()),
		arg_option_name,
		core::demangle(arg_option_type.name()))
	, option_name(arg_option_name)
	, get_type(arg_get_type)
	, option_type(arg_option_type)
    { }
    string option_name;
    const std::type_info& get_type;
    const std::type_info& option_type;
};

struct bad_option_error : public error
{
    bad_option_error(string_view arg_option_name, const std::type_info& arg_get_type)
	: error("attempted to extract type '{}' from option '{}' which is not defined.",
		core::demangle(arg_get_type.name()),
		arg_option_name)
	, option_name(arg_option_name)
	, get_type(arg_get_type)
    { }
    string option_name;
    const std::type_info& get_type;
};

struct missing_value_error : public error
{
    using error::error;
};

struct bad_value_error : public error
{
    using error::error;
};

}; // core::argp
