// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <queue>
#include "core/common.h"

namespace core::argp
{

using Tokens = std::queue<string_view>;
static constexpr char OptionSymbol = '-';

bool is_first_identifier(char c)
{
    return (c >= 'a' and c <= 'z')
	or (c >= 'A' and c <= 'Z');
}
    
bool is_long_option(string_view arg)
{
    return arg.size() > 2
	and arg[0] == OptionSymbol
	and arg[1] == OptionSymbol
	and is_first_identifier(arg[2]);
}
    
bool is_short_option(string_view arg)
{
    return arg.size() == 2
	and arg[0] == OptionSymbol
	and is_first_identifier(arg[1]);
}

bool is_option_separator(string_view arg)
{
    return arg.size() == 2
	and arg[0] == OptionSymbol
	and arg[1] == OptionSymbol;
}

bool is_option(string_view arg)
{
    return is_long_option(arg)
	or is_short_option(arg);
}

}; // core::argp
