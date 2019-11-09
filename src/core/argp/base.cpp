// Copyright (C) 2019 by Mark Melton
//

#include "core/argp/base.h"

namespace core::argp
{

bool is_identifier(char c)
{
    return (c >= 'a' and c <= 'z')
	or (c >= 'A' and c <= 'Z');
}
    
bool is_long_option(string_view arg)
{
    return arg.size() > 2
	and arg[0] == OptionSymbol
	and arg[1] == OptionSymbol
	and is_identifier(arg[2]);
}
    
bool is_short_option(string_view arg)
{
    return arg.size() == 2
	and arg[0] == OptionSymbol
	and is_identifier(arg[1]);
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

bool is_option_group(string_view arg)
{
    return arg.size() > 2
	and arg[0] == OptionSymbol
	and is_identifier(arg[1])
	and is_identifier(arg[2]);
}

string make_spec(string_view arg_value, size_t min, size_t max)
{
    string value = string(arg_value);
    string r;
    if (min == 0);
    else if (min == 1) r = value + " ";
    else if (min == 2) r = value + " " + value + " ";
    else if (min > 2) return value + " " + value + " ... ";

    if (max - min == 0);
    else if (max - min == 1) r += "[" + value + "]";
    else if (max - min == 2) r += "[" + value + " [" + value + "]]";
    else r += "[" + value + " [...]]";

    return r;
}

}; // core::argp
