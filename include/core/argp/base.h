// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <queue>
#include "core/common.h"

namespace core::argp
{

static constexpr char OptionSymbol = '-';

bool is_identifier(char c);
bool is_long_option(string_view arg);
bool is_short_option(string_view arg);
bool is_option_separator(string_view arg);
bool is_option(string_view arg);
bool is_option_group(string_view arg);

string make_spec(string_view arg_value, size_t min, size_t max);

}; // core::argp
