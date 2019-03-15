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

    void process_token(string_view token, Tokens& tokens)
    {
	using core::tp::find_first;
	using core::tp::apply_nth;
		
	auto idx = find_first(m_tuple, [&](const auto& e) { return e.matches(token); });

	if (idx < 0)
	{
	    if (token == "-*") throw unknown_option_error(tokens.front());
	    else throw unknown_option_error(token);
	}
	
	apply_nth(m_tuple, idx, [&](auto& e) { e.match(token, tokens); });
    }

    bool parse(const strings& args)
    {
	Tokens tokens;
	for (const auto& arg : args)
	    tokens.emplace(arg);
	tokens.pop();

	bool done_with_options{false};
	while (tokens.size() > 0)
	{
	    auto token = tokens.front();
	    tokens.pop();
	    
	    if (done_with_options or token[0] != OptionSymbol)
	    {
		tokens.push(token);
		process_token("-*", tokens);
	    }
	    else if (is_option_separator(token))
	    {
		done_with_options = true;
	    }
	    else if (is_option(token))
	    {
		process_token(token, tokens);
	    }
	    else if (is_option_group(token))
	    {
		for (auto c : token.substr(1))
		    process_token(string{'-', c}, tokens);
	    }
	    else
		throw unknown_option_error(token);
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

namespace interface
{
using core::argp::ArgParse;
using core::argp::ArgFlag;
using core::argp::ArgFlagApply;
using core::argp::ArgFlagCount;
using core::argp::ArgStore;
using core::argp::ArgStoreContainer;
};

}; // argp

using namespace argp::interface;

}; // core


