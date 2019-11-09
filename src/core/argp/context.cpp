// Copyright (C) 2019 by Mark Melton
//

#include "core/argp/context.h"

namespace core::argp
{

Context::Context(const strings& args)
    : m_index(0)
{
    for (const auto& arg : args)
	m_tokens.push_back(arg);
}

bool Context::end() const
{
    return m_index >= m_tokens.size();
}

string_view Context::front() const
{
    return m_tokens[m_index];
}

void Context::pop()
{
    if (m_index < m_tokens.size())
	++m_index;
}

const strings& Context::tokens() const
{
    return m_tokens;
}

string Context::canonical_line() const
{
    string line;
    for (const auto& token : m_tokens)
    {
	line += " ";
	line += token;
    }
    return line;
}

string Context::canonical_marker() const
{
    string line;
    for (const auto& token : m_tokens)
    {
	line += " ";
	if (token == front())
	    line += "^";
	line += string(token.size(), ' ');
    }
    return line;
}


}; // core::argp
