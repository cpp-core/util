// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <typeinfo>
#include "core/common.h"

namespace core::argp
{

static constexpr auto bad_type_msg = "cannot extract type '{}' from option '{}'"
    " which is actually of type '{}'.";
static constexpr auto bad_option_msg = "cannot extract type '{}' from option '{}'"
    " which is not defined.";
static constexpr auto missing_value_msg = "no value supplied for option '{}' with type '{}'";
static constexpr auto bad_value_msg = "cannot parse user string '{}' as type '{}' for option '{}'";

struct error : public std::runtime_error
{
    using base = std::runtime_error;
    using base::base;
};

struct bad_type_error : public error
{
    bad_type_error(string_view arg_option_name, const std::type_info& arg_get_type,
		   const std::type_info& arg_option_type);
    string option_name;
    const std::type_info& get_type;
    const std::type_info& option_type;
};

struct bad_option_error : public error
{
    bad_option_error(string_view arg_option_name, const std::type_info& arg_get_type);
    string option_name;
    const std::type_info& get_type;
};

struct missing_value_error : public error
{
    missing_value_error(string_view arg_option_name, const std::type_info& arg_option_type);
    string option_name;
    const std::type_info& option_type;
};

struct bad_value_error : public error
{
    bad_value_error(string_view arg_option_name, const std::type_info& arg_option_type,
		    string_view arg_user_token);
    string option_name, user_token;
    const std::type_info& option_type;
};

}; // core::argp
