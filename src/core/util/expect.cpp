// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include "core/util/expect.h"

namespace core::expect::detail
{

void expect_bool(bool a, const char *astr, bool v, const char *vstr,
                 const char *func, const char *file, int line)
{
    if (not (a == v))
    {
        throw core::expect_exception("{}:{}:{}:\n"
                                     "  expectation: {} is {}\n"
                                     "  failed     : {}",
                                     file, line, func,
                                     astr, vstr,
                                     a);
    }
}


}; // end ns core::expect::detail
