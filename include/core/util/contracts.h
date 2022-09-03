// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include <exception>
#include <stdexcept>

namespace core {

void Expects(bool cond)
{
    assert(cond);
}

void Ensures(bool cond)
{
    assert(cond);
}

}; // end ns core
