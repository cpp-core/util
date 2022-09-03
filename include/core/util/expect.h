// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <fmt/printf.h>
#include "core/util/common.h"

namespace core
{

struct expect_exception : public core::runtime_error
{
    using Base = core::runtime_error;
    using Base::Base;
    
    template<class... Args>
    expect_exception(std::string_view spec, const Args&... args)
	: Base(spec, args...)
    { }
};

namespace expect::detail
{

template<class T, class U, class Predicate>
void expect(T&& a, U&& b, const char *astr, const char *bstr,
	    Predicate predicate, const char *pstr,
	    const char *func, const char *file, int line)
{
    if (not bool(predicate(a, b)))
    {
	throw core::expect_exception("{}:{}:{}:\n"
				     "  expectation: {} {} {}\n"
				     "  failed with: {} {} {}",
				     file, line, func,
				     astr, pstr, bstr,
				     a, pstr, b);
    }
}

void expect_bool(bool a, const char *astr, bool v, const char *vstr,
		 const char *func, const char *file, int line);

#define ExpectEQ(A,B)							\
    core::expect::detail::expect(A, B, #A, #B,				\
				  std::equal_to<decltype(A)>{}, "==",	\
				  __func__, __FILE__, __LINE__)

#define ExpectNE(A,B)							\
    core::expect::detail::expect(A, B, #A, #B,				\
				  std::not_equal_to<decltype(A)>{}, "!=",	\
				  __func__, __FILE__, __LINE__)

#define ExpectLT(A,B)							\
    core::expect::detail::expect(A, B, #A, #B,				\
				  std::less<decltype(A)>{}, "<",	\
				  __func__, __FILE__, __LINE__)

#define ExpectLE(A,B)							\
    core::expect::detail::expect(A, B, #A, #B,				\
				  std::less_equal<decltype(A)>{}, "<=",	\
				  __func__, __FILE__, __LINE__)

#define ExpectGT(A,B)							\
    core::expect::detail::expect(A, B, #A, #B,				\
				  std::greater<decltype(A)>{}, ">",	\
				  __func__, __FILE__, __LINE__)

#define ExpectGE(A,B)							\
    core::expect::detail::expect(A, B, #A, #B,				\
				  std::greater_equal<decltype(A)>{}, ">=", \
				  __func__, __FILE__, __LINE__)

#define ExpectTRUE(A)							\
    core::expect::detail::expect_bool(bool(A), #A, true, "true",	\
				      __func__, __FILE__, __LINE__)

#define ExpectFALSE(A)							\
    core::expect::detail::expect_bool(bool(A), #A, false, "false",	\
				      __func__, __FILE__, __LINE__)

#define EnsureEQ ExpectEQ
#define EnsureNE ExpectNE
#define EnsureGT ExpectGT
#define EnsureGE ExpectGE
#define EnsureLT ExpectLT
#define EnsureLE ExpectLE
#define EnsureTRUE ExpectTRUE
#define EnsureFALSE ExpectFALSE

}; // end ns expect::detail
}; // end ns core
