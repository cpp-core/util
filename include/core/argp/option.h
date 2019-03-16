// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/argp/base.h"
#include "core/argp/error.h"
#include "core/demangle.h"
#include "core/string/lexical_cast.h"

namespace core::argp
{

struct noop { constexpr void operator()() const noexcept { } };

struct ArgBase
{
    ArgBase(char arg_short_name, string_view arg_long_name, string_view arg_description);
    bool matches(string_view token) const;

    char short_name;
    string long_name;
    string description;
    string value_spec;
    size_t count{0};
};

template<class F>
struct ArgFlag : ArgBase
{
    ArgFlag(char short_name, string_view long_name, string_view description, F&& func = noop{})
	: ArgBase(short_name, long_name, description)
	, function(std::move(func))
    { }

    void match(string_view token, Tokens& tokens)
    {
	++count;
	value = true;
	function();
    }
    
    bool value{false};
    F function;
};

ArgFlag(char, string_view, string_view) -> ArgFlag<noop>;

template<class T, bool Overwrite = true>
struct ArgStore : ArgBase
{
    ArgStore(char short_name, string_view long_name, string_view description, T default_value)
	: ArgBase(short_name, long_name, description)
	, value(default_value)
    {
	if (short_name == '*') value_spec = make_spec(long_name, 1, 1);
	else value_spec = make_spec(core::type_name<T>(), 1, 1);
    }
    
    void match(string_view token, Tokens& tokens)
    {
	if (tokens.size() == 0 or is_option(tokens.front()))
	    throw missing_value_error(long_name, typeid(T));
	
	auto str = tokens.front();
	tokens.pop();
	
	try { value = core::lexical_cast<T>(str); }
	catch (const core::lexical_cast_error& error)
	{ throw bad_value_error(long_name, typeid(T), str); }

	if (count > 0 and not Overwrite)
	    throw std::runtime_error("Option seen twice.");
	++count;
    }

    T value;
};

template<template<class...> class C, class T,
	 size_t Min = 1, size_t Max = std::numeric_limits<size_t>::max()>
struct ArgStoreContainer : ArgBase
{
    ArgStoreContainer(char short_name, string_view long_name, string_view description)
	: ArgBase(short_name, long_name, description)
    {
	if (short_name == '*') value_spec = make_spec(long_name, Min, Max);
	else value_spec = make_spec(core::type_name<T>(), Min, Max);
    }
    
    void match(string_view token, Tokens& tokens)
    {
	while (tokens.size() > 0 and not is_option(tokens.front()))
	{
	    auto str = tokens.front();
	    tokens.pop();
	    
	    try { value.emplace_back(core::lexical_cast<T>(str)); }
	    catch (const core::lexical_cast_error& error)
	    { throw bad_value_error(long_name, typeid(T), str); }
	}

	auto count = value.size();
	if (count < Min)
	    throw too_few_values_error(long_name, typeid(T), count, Min);
	else if (count > Max)
	    throw too_many_values_error(long_name, typeid(T), count, Max);
    }

    C<T> value;
};

}; // core::argp
