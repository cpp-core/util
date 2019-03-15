// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/argp/base.h"
#include "core/argp/error.h"
#include "core/string/lexical_cast.h"

namespace core::argp
{

struct ArgBase
{
    ArgBase(char arg_short_name, string_view arg_long_name, string_view arg_description)
	: short_name(arg_short_name)
	, long_name(arg_long_name)
	, description(arg_description)
    { }
    
    bool matches(string_view token) const
    {
	if (token.size() == 2 and token[0] == OptionSymbol)
	    return token[1] == short_name;
	if (token.size() == long_name.size() + 2
	    and token[0] == OptionSymbol
	    and token[1] == OptionSymbol)
	    return token.substr(2) == long_name;
	return false;
    }

    char short_name;
    string long_name;
    string description;
};

struct ArgFlag : ArgBase
{
    using ArgBase::ArgBase;
    
    void match(string_view token, Tokens& tokens)
    { value = true; }

    bool value{false};
};

template<class F>
struct ArgFlagApply : ArgBase
{
    ArgFlagApply(char short_name, string_view long_name, string_view description, F&& func)
	: ArgBase(short_name, long_name, description)
	, function(std::move(func))
    { }

    void match(string_view token, Tokens& tokens)
    {
	value = true;
	function();
    }
    
    bool value{false};
    F function;
};

struct ArgFlagCount : ArgBase
{
    using ArgBase::ArgBase;

    void match(string_view token, Tokens& tokens)
    { ++value; }

    size_t value{0};
};

template<class T>
struct ArgStore : ArgBase
{
    ArgStore(char short_name, string_view long_name, string_view description, T default_value)
	: ArgBase(short_name, long_name, description)
	, value(default_value)
    { }
    
    void match(string_view token, Tokens& tokens)
    {
	if (tokens.size() == 0)
	    throw missing_value_error(long_name);
	
	auto str = tokens.front();
	tokens.pop();
	try { value = core::lexical_cast<T>(str); }
	catch (const core::lexical_cast_error& error) { throw bad_value_error(str); }
    }

    T value;
};

}; // core::argp
