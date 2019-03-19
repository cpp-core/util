// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <typeinfo>
#include "core/common.h"

namespace core::argp
{

static constexpr auto unknown_option_msg = "unknown option '{}'.";
static constexpr auto missing_value_msg = "no value supplied for option '{}' with type '{}'";
static constexpr auto bad_value_msg = "cannot parse user string '{}' as type '{}' for option '{}'";
static constexpr auto too_few_values_msg =
    "needed at least {} value(s) of type '{}' for option '{}', but found {}";
static constexpr auto too_many_values_msg =
    "needed at most {} value(s) of type '{}' for option '{}', but found {}";

struct error : public std::runtime_error
{
    using base = std::runtime_error;
    using base::base;
};

struct unknown_option_error : public error
{
    unknown_option_error(string_view arg_option_name);
    string option_name;
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

struct too_few_values_error : public error
{
    too_few_values_error(string_view arg_option_name, const std::type_info& arg_option_type,
			 size_t number_found, size_t number_needed);
    string option_name;
    const std::type_info& option_type;
    size_t number_found;
    size_t number_min;
};

struct too_many_values_error : public error
{
    too_many_values_error(string_view arg_option_name, const std::type_info& arg_option_type,
			  size_t arg_number_found, size_t arg_number_max);
    string option_name;
    const std::type_info& option_type;
    size_t number_found;
    size_t number_max;
};

}; // core::argp
