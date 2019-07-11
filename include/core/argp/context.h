// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/argp/base.h"

namespace core::argp
{

class Context
{
public:
    Context(const strings& args);

    bool end() const;
    const string& front() const;
    void pop();
    
private:
    size_t m_index;
    strings m_tokens;
};

}; // core::argp
