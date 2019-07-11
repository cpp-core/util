// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <any>
#include "core/argp/base.h"
#include "core/argp/context.h"
#include "core/argp/error.h"
#include "core/tuple/apply.h"
#include "core/tuple/find.h"
#include "core/tuple/map.h"
#include "core/mp/constants.h"
#include "core/mp/find_index.h"
#include "core/mp/transform.h"

namespace core
{

namespace argp
{

template<class T>
using flag_character = core::mp::_char<T::FlagCharacter>;

template<class... Ts>
class ArgParse
{
public:
    using Tuple = std::tuple<Ts...>;
    using Flags = core::mp::transform_t<flag_character, core::mp::list<Ts...>>;
    
    ArgParse(Ts&&... args)
	: m_tuple(std::make_tuple(std::move(args)...))
    { }

    template<char C>
    auto get()
    {
	constexpr auto Index = core::mp::find_index_v<Flags, core::mp::_char<C>>;
	static_assert(Index < std::tuple_size_v<Tuple>, "\n\n"
		      "static assertion: No option with the given name exists.\n"
		      "static assertion: Ignore subsequent compiler errors for the next line.\n");
	return std::get<Index>(m_tuple).value;
    }

    template<char C>
    auto get_count()
    {
	constexpr auto Index = core::mp::find_index_v<Flags, core::mp::_char<C>>;
	static_assert(Index < std::tuple_size_v<Tuple>, "\n\n"
		      "static assertion: No option with the given name exists.\n"
		      "static assertion: Ignore subsequent compiler errors for the next line.\n");
	return std::get<Index>(m_tuple).count;
    }

    void process_token(string_view token, Context& ctx)
    {
	using core::tp::find_first;
	using core::tp::apply_nth;
		
	auto idx = find_first(m_tuple, [&](const auto& e) { return e.matches(token); });

	if (idx < 0)
	{
	    if (token == "-*") throw unknown_option_error(string(token), ctx);
	    else throw unknown_option_error(string(token), ctx);
	}
	
	apply_nth([&](auto& e) { e.match(token, ctx); }, idx, m_tuple);
    }

    string star_value_spec()
    {
	auto printer = [&](const auto& result, const auto& arg)
		       {
			   if (arg.FlagCharacter != '*')
			       return result;
			   return result + " " + arg.value_spec;
		       };
	return core::tp::fold_l(printer, string(), m_tuple);
    }
    
    void output_help_message(std::ostream& os, const strings& args)
    {
	auto program_name = args.size() > 0 ? args[0] : "no program name";
	cout << "program: " << program_name << " [options]" << star_value_spec() << endl;
	auto printer = [&](const auto& arg)
		       {
			   if (arg.FlagCharacter == '*')
			       return;
			   
			   auto n = 20 - arg.long_name.size() - arg.value_spec.size();
			   if (n < 1) n = 1;
			   
			   os << "\t";
			   os << "-" << arg.FlagCharacter << ", ";
			   os << "--" << arg.long_name << " ";
			   os << arg.value_spec;
			   os << string(n, ' ');
			   os << arg.description << endl;
		       };
	core::tp::apply(printer, m_tuple);
    }

    bool parse(const strings& args)
    {
	Context ctx{args};
	ctx.pop();
	
	bool done_with_options{false};
	while (not ctx.end())
	{
	    const auto& token = ctx.front();
	    if (done_with_options or token[0] != OptionSymbol)
	    {
		process_token("-*", ctx);
	    }
	    else if (ctx.front() == "--help")
	    {
		output_help_message(cout, args);
		exit(0);
	    }
	    else if (is_option_separator(token))
	    {
		ctx.pop();
		done_with_options = true;
	    }
	    else if (is_option(token))
	    {
		ctx.pop();
		process_token(token, ctx);
	    }
	    else if (is_option_group(token))
	    {
		ctx.pop();
		for (auto c : token.substr(1))
		    process_token(string{'-', c}, ctx);
	    }
	    else
		throw unknown_option_error(string(token), ctx);
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
using core::argp::argFlag;
using core::argp::argValue;
using core::argp::argValues;

};

}; // argp

using namespace argp::interface;

}; // core


