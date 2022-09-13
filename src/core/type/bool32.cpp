// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <bit>
#include "core/type/bool32.h"

namespace core {
inline namespace type {
       
bool32::reference::reference()
    : m_ptr(nullptr)
    , m_mask(0)
{ }
	
bool32::reference::reference(std::uint32_t *ptr, std::uint32_t mask)
    : m_ptr(ptr)
    , m_mask(mask)
{ }
	
bool32::reference& bool32::reference::operator=(bool x) noexcept {
    if (x) *m_ptr |= m_mask;
    else *m_ptr &= ~m_mask;
    return *this;
}

std::ostream& operator<<(std::ostream& os, bool32 value) {
    for (auto i = 0; i < 32; ++i)
	os << value[i];
    return os;
}

bool32& bool32::operator&=(bool32 b) {
    m_value &= b.m_value;
    return *this;
}

bool32& bool32::operator|=(bool32 b) {
    m_value |= b.m_value;
    return *this;
}

bool32& bool32::operator^=(bool32 b) {
    m_value ^= b.m_value;
    return *this;
}

bool32& bool32::operator+=(bool32 b) {
    m_value += b.m_value;
    return *this;
}

bool32& bool32::operator-=(bool32 b) {
    m_value -= b.m_value;
    return *this;
}

bool32 operator~(bool32 a) {
    return ~a.as_uint();
}

bool32 operator&(bool32 a, bool32 b) {
    return a &= b;
}

bool32 operator|(bool32 a, bool32 b) {
    return a |= b;
}

bool32 operator^(bool32 a, bool32 b) {
    return a ^= b;
}

bool32 operator+(bool32 a, bool32 b) {
    return a += b;
}

bool32 operator-(bool32 a, bool32 b) {
    return a -= b;
}

bool32 rotr(bool32 a, uint n) {
    return std::rotr(a.as_uint(), n);
}

bool32 operator>>(bool32 a, uint n) {
    return a.as_uint() >> n;
}

bool any(bool32 a) {
    return a.any();
}

bool all(bool32 a) {
    return a.all();
}

bool none(bool32 a) {
    return a.none();
}

}; // type
}; // core
