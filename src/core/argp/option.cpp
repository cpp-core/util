// Copyright (C) 2019 by Mark Melton
//

#include "core/argp/option.h"

namespace core::argp
{

// ArgBase::ArgBase(char arg_short_name, string_view arg_long_name, string_view arg_description)
//     : short_name(arg_short_name)
//     , long_name(arg_long_name)
//     , description(arg_description)
// { }

// bool ArgBase::matches(string_view token) const
// {
//     if (token.size() == 2 and token[0] == OptionSymbol)
// 	return token[1] == short_name;
//     if (token.size() == long_name.size() + 2
// 	and token[0] == OptionSymbol
// 	and token[1] == OptionSymbol)
// 	return token.substr(2) == long_name;
//     return false;
// }

}; // core::argp
