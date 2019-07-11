// Copyright (C) 2019 by Mark Melton
//

#pragma once

namespace core::argp
{

static constexpr auto unknown_option_msg = "unknown option '{}'.";
static constexpr auto missing_value_msg = "no value supplied for option '{}' with type '{}'";
static constexpr auto bad_value_msg = "cannot parse user string '{}' as type '{}' for option '{}'";
static constexpr auto too_few_values_msg =
    "needed at least {} value(s) of type '{}' for option '{}', but found {}";
static constexpr auto too_many_values_msg =
    "needed at most {} value(s) of type '{}' for option '{}', but found {}";

}; // core::argp
