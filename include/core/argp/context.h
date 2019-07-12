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
    string_view front() const;
    void pop();

    const strings& tokens() const;
    string canonical_line() const;
    string canonical_marker() const;
    
private:
    size_t m_index;
    strings m_tokens;
};

}; // core::argp
