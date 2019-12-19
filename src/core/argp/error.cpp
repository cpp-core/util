// Copyright (C) 2019 by Mark Melton
//

#include <fmt/format.h>
#include "core/argp/error.h"
#include "core/argp/message.h"
#include "core/demangle.h"

namespace core::argp
{

error::error(string_view msg, const Context& ctx)
    : std::runtime_error(string(msg))
    , context(ctx)
{ }

error_type::error_type(string_view msg, const Context& ctx, const std::type_info& type)
    : error(msg, ctx)
    , option_type(type)
{ }

error_count::error_count(string_view msg,
			 const Context& ctx,
			 const std::type_info& option_type,
			 size_t arg_number_found,
			 size_t arg_number_limit)
    : error_type(msg, ctx, option_type)
    , number_found(arg_number_found)
    , number_limit(arg_number_limit)
{ }

unknown_option_error::unknown_option_error(string_view name, const Context& ctx)
    : error(fmt::format(unknown_option_msg, name), ctx)
{ }

missing_value_error::missing_value_error(string_view name,
					 const Context& ctx,
					 const std::type_info& type)
    : error_type(fmt::format(missing_value_msg, name, core::demangle(type.name())), ctx, type)
{ }

bad_value_error::bad_value_error(string_view name,
				 const Context& ctx,
				 const std::type_info& type)
    : error_type(fmt::format(bad_value_msg, ctx.front(), core::demangle(type.name()), name),
		 ctx, type)
{ }

too_few_values_error::too_few_values_error(string_view name,
					   const Context& ctx,
					   const std::type_info& type,
					   size_t number_found,
					   size_t number_limit)
    : error_count(fmt::format(too_few_values_msg, number_limit, core::demangle(type.name()),
			      name, number_found),
		  ctx, type, number_found, number_limit)
{ }

too_many_values_error::too_many_values_error(string_view name,
					     const Context& ctx,
					     const std::type_info& type,
					     size_t number_found,
					     size_t number_limit)
    : error_count(fmt::format(too_many_values_msg, number_limit, core::demangle(type.name()),
			      name, number_found),
		  ctx, type, number_found, number_limit)
{ }

}; // core::argp
