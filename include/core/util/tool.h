// Copyright (C) 2017, 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <fstream>
#include "core/util/common.h"
#include "core/argp/parse.h"
#include "core/string/lexical_cast.h"

using namespace core::argp::interface;

int tool_main(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    cout << std::boolalpha;
    
    try
    {
	return tool_main(argc, argv);
    }
    catch (core::expect_exception const& e)
    {
	cerr << e.what() << endl;
	return -2;
    }
    catch (core::lexical_cast_error const& e)
    {
	cerr << "lexical_cast_error: " << e.what() << endl;
	return -2;
    }
    catch (core::argp::error const& e)
    {
	cerr << "argp_error: " << e.context.canonical_line() << endl;
	cerr << "argp_error: " << e.context.canonical_marker() << endl;
	cerr << "argp_error: " << e.what() << endl;
	return -2;
    }
    catch (std::runtime_error const& e)
    {
	cerr << "runtime_error: " << e.what() << endl;
	return -2;
    }
    catch (std::exception const& e)
    {
	cerr << e.what() << endl;
	return -2;
    }
    catch (...)
    {
	cerr << "unknown error: " << endl;
	return -1;
    }
}
