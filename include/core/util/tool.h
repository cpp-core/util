// Copyright (C) 2017, 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <iostream>
#include "core/util/exception.h"
// #include "core/argp/parse.h"
#include "core/string/lexical_cast.h"

// using namespace core::argp::interface;

int tool_main(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    std::cout << std::boolalpha;
    
    try
    {
	return tool_main(argc, argv);
    }
    catch (core::str::lexical_cast_error const& e)
    {
	std::cerr << "lexical_cast_error: " << e.what() << std::endl;
	return -2;
    }
    // catch (core::argp::error const& e)
    // {
    // 	std::cerr << "argp_error: " << e.context.canonical_line() << std::endl;
    // 	std::cerr << "argp_error: " << e.context.canonical_marker() << std::endl;
    // 	std::cerr << "argp_error: " << e.what() << std::endl;
    // 	return -2;
    // }
    catch (std::runtime_error const& e)
    {
	std::cerr << "runtime_error: " << e.what() << std::endl;
	return -2;
    }
    catch (std::exception const& e)
    {
	std::cerr << e.what() << std::endl;
	return -2;
    }
    catch (...)
    {
	std::cerr << "unknown error: " << std::endl;
	return -1;
    }
}
