// Copyright (C) 2019, 2022 by Mark Melton
//

#include <random>
#include "core/util/guid.h"

namespace core
{

Guid Guid::generate()
{
    static constexpr size_t BytesPerSample = sizeof(std::random_device::result_type);
    static std::random_device engine;
	
    Guid guid;
    auto ptr = guid.begin();
    while (ptr < guid.end())
    {
	auto rbits = engine();
	size_t i = 0;
	while (ptr < guid.end() and i < BytesPerSample)
	{
	    *ptr = rbits & 0xFF;
	    rbits >>= 8;
	    ++ptr;
	    ++i;
	}
    }
    return guid;
}

bool Guid::nil() const
{
    for (auto ptr = m_bytes.begin(); ptr != m_bytes.end(); ++ptr)
	if (*ptr != 0)
	    return false;
    return true;
}

std::string Guid::as_string() const
{
    std::string r;
    r.reserve(36);
    size_t idx{1};
    for (auto ptr = begin(); ptr != end(); ++ptr, ++idx)
    {
	auto upper = (*ptr >> 4) bitand 0x0F;
	auto lower = (*ptr bitand 0x0F);
	auto cupper = upper >= 10 ? upper - 10 + 'a' : upper + '0';
	auto clower = lower >= 10 ? lower - 10 + 'a' : lower + '0';
	r.push_back(cupper);
	r.push_back(clower);
	if (idx == 4 or idx == 6 or idx == 8 or idx == 10)
		r.push_back('-');
    }
    return r;
}

}; // core

std::ostream& operator<<(std::ostream& os, const core::Guid& guid)
{
    os << guid.as_string();
    return os;
}

