// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <typeinfo>
#include "core/utility/common.h"
#include "core/argp/context.h"

namespace core::argp
{

struct error : public std::runtime_error
{
    error(string_view msg, const Context& arg_ctx);
    Context context;
};

struct error_type : public error
{
    error_type(string_view msg, const Context& ctx, const std::type_info& arg_option_type);
    const std::type_info& option_type;
};

struct error_count : public error_type
{
    error_count(string_view msg, const Context& ctx, const std::type_info& option_type,
		size_t arg_number_found, size_t arg_number_limit);
    size_t number_found, number_limit;
};

struct unknown_option_error : public error
{
    unknown_option_error(string_view name, const Context& ctx);
};

struct missing_value_error : public error_type
{
    missing_value_error(string_view name, const Context& ctx, const std::type_info& type);
};

struct bad_value_error : public error_type
{
    bad_value_error(string_view name, const Context& ctx, const std::type_info& type);
};

struct too_few_values_error : public error_count
{
    too_few_values_error(string_view name, const Context& ctx, const std::type_info& type,
			 size_t number_found, size_t number_needed);
};

struct too_many_values_error : public error_count
{
    too_many_values_error(string_view name, const Context& ctx, const std::type_info& type,
			  size_t arg_number_found, size_t arg_number_max);
};

}; // core::argp
