// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <any>
#include "core/argp/base.h"
#include "core/argp/error.h"
#include "core/tuple/find.h"

namespace core
{

namespace argp
{

template<class... Ts>
class ArgParse
{
public:
    using Tuple = std::tuple<Ts...>;
    ArgParse(Ts&&... args)
	: m_tuple(std::make_tuple(std::move(args)...))
    { }

    template<class T>
    T get(string long_name)
    {
	using core::tp::find_first;
	using core::tp::apply_nth;
	
	auto idx = find_first(m_tuple, [&](const auto& e) { return e.long_name == long_name; });
	if (idx < 0) throw get_option_error(long_name);

	auto value = apply_nth(m_tuple, idx, [&](const auto& e) { return std::any(e.value); });
	auto *ptr = std::any_cast<T>(&value);
	if (ptr == nullptr)
	    throw get_type_error(long_name, typeid(T), value.type());
	return *ptr;
    }

    bool parse(const strings& args)
    {
	Tokens tokens;
	for (const auto& arg : args)
	    tokens.emplace(arg);

	while (tokens.size() > 0)
	{
	    auto token = tokens.front();
	    tokens.pop();

	    if (is_option(token))
	    {
		using core::tp::find_first;
		using core::tp::apply_nth;
		
		auto idx = find_first(m_tuple, [&](const auto& e) { return e.matches(token); });
		
		if (idx < 0)
		    throw unknown_option_error(token);

		apply_nth(m_tuple, idx, [&](auto& e) { return e.match(token, tokens); });
	    }
	    else
	    {
		m_extra.push_back(string(token));
	    }
	}
	
	return true;
    }
    
    bool parse(std::initializer_list<string> largs)
    {
	strings args(largs.begin(), largs.end());
	return parse(args);
    }
    
    bool parse(int argc, const char *argv[])
    {
	strings args;
	for (size_t i = 0; i < size_t(argc); ++i)
	    args.emplace_back(std::move(string(argv[i])));
	return parse(args);
    }
    
private:
    Tuple m_tuple;
    strings m_extra;
};

}; // argp

using argp::ArgParse;
using argp::ArgFlag;
using argp::ArgFlagApply;
using argp::ArgFlagCount;
using argp::ArgStore;
using argp::ArgStoreContainer;

}; // core
