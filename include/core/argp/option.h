// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/argp/base.h"
#include "core/argp/error.h"
#include "core/demangle.h"
#include "core/string/lexical_cast.h"

namespace core::argp
{

struct noop
{
    template<class... Ts>
    constexpr void operator()(Ts&...) const noexcept { }
};
struct ident { constexpr bool operator()() const noexcept { return true; } };

template<char C>
struct ArgBase
{
    static constexpr char FlagCharacter = C;

    ArgBase(string_view arg_long_name, string_view arg_description)
	: long_name(arg_long_name)
	, description(arg_description)
    { }

    bool matches(string_view token) const
    {
	if (token.size() == 2 and token[0] == OptionSymbol)
	    return token[1] == FlagCharacter;
	if (token.size() == long_name.size() + 2
	    and token[0] == OptionSymbol
	    and token[1] == OptionSymbol)
	    return token.substr(2) == long_name;
	return false;
    }

    string long_name;
    string description;
    string value_spec;
    size_t count{0};
};

template<char C, class F>
struct ArgFlag : ArgBase<C>
{
    ArgFlag(string_view long_name, string_view description, F&& func)
	: ArgBase<C>(long_name, description)
	, function(std::move(func))
    { }

    void match(string_view token, Tokens& tokens)
    {
	++this->count;
	value = true;
	function();
    }
    
    bool value{false};
    F function;
};

template<char C>
auto argFlag(string_view long_name, string_view description)
{ return ArgFlag<C,noop>(long_name, description, std::move(noop{})); }

template<char C, class F>
auto argFlag(string_view long_name, string_view description, F&& func = noop{})
{ return ArgFlag<C,F>(long_name, description, std::move(func)); }

template<char C, class T, class F>
struct ArgValue : ArgBase<C>
{
    using Base = ArgBase<C>;
    ArgValue(string_view long_name, T default_value, string_view description, F&& func)
	: Base(long_name, description)
	, value(default_value)
	, function(std::move(func))
    {
	if (Base::FlagCharacter == '*') Base::value_spec = make_spec(long_name, 1, 1);
	else Base::value_spec = make_spec(core::type_name<T>(), 1, 1);
    }
    
    void match(string_view token, Tokens& tokens)
    {
	if (tokens.size() == 0 or is_option(tokens.front()))
	    throw missing_value_error(Base::long_name, typeid(T));
	
	auto str = tokens.front();
	tokens.pop();
	
	try { value = core::lexical_cast<T>(str); }
	catch (const core::lexical_cast_error& error)
	{ throw bad_value_error(Base::long_name, typeid(T), str); }

	function(value);
	++Base::count;
    }

    T value;
    F function;
};

template<char C, class T>
auto argValue(string_view long_name, string_view description)
{ return ArgValue<C,T,noop>(long_name, T{}, description, std::move(noop{})); }

template<char C, class T>
auto argValue(string_view long_name, T default_value, string_view description)
{ return ArgValue<C,T,noop>(long_name, default_value, description, std::move(noop{})); }

template<char C, class T, class F>
auto argValue(string_view long_name, string_view description, F&& func)
{ return ArgValue<C,T,F>(long_name, T{}, description, std::move(func)); }

template<char C, class T, class F>
auto argValue(string_view long_name, T default_value, string_view description, F&& func)
{ return ArgValue<C,T,F>(long_name, default_value, description, std::move(func)); }

/*
template<template<class...> class C, class T,
	 size_t Min = 1, size_t Max = std::numeric_limits<size_t>::max()>
struct ArgValueContainer : ArgBase
{
    ArgValueContainer(char short_name, string_view long_name, string_view description)
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
*/
}; // core::argp
