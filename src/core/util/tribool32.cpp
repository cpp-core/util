// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <bit>
#include <fmt/format.h>
#include "core/util/tribool32.h"

namespace core {
inline namespace util {
       
tribool32::reference::reference()
    : m_ptr_true(nullptr)
    , m_ptr_false(nullptr)
    , m_mask(0)
{ }
	
tribool32::reference::reference(std::uint32_t *ptr_true, std::uint32_t *ptr_false, std::uint32_t mask)
    : m_ptr_true(ptr_true)
    , m_ptr_false(ptr_false)
    , m_mask(mask)
{ }

tribool32::reference& tribool32::reference::operator=(tribool x) noexcept {
    if (x.is_true()) *m_ptr_true |= m_mask;
    else if (x.is_false()) *m_ptr_false |= m_mask;
    return *this;
}
	
tribool32::reference& tribool32::reference::operator=(const reference& x) noexcept {
    return *this = tribool(x);
}

tribool32::reference::operator tribool() const noexcept {
    return tribool{bool(*m_ptr_true & m_mask), bool(*m_ptr_false & m_mask)};
}

tribool32::tribool32()
    : m_true(0)
    , m_false(0)
{ }
    
tribool32::tribool32(bool value)
    : m_true(value ? ~Value{0} : 0)
    , m_false(~m_true)
{ }
    
tribool32::tribool32(std::uint32_t value)
    : m_true(value)
    , m_false(~m_true)
{ }
    
tribool32::tribool32(bool32 value)
    : m_true(value.as_uint())
    , m_false(~m_true)
{ }
    
tribool32::tribool32(std::uint32_t mask_true, std::uint32_t mask_false)
    : m_true(mask_true)
    , m_false(mask_false)
{
    if (mask_true & mask_false)
	throw std::runtime_error
	    (fmt::format("tribool: cannot be both true and false: {:b} {:b} ==> {:b}",
			 mask_true, mask_false, mask_true & mask_false));
}

tribool32::tribool32(bool32 mask_true, bool32 mask_false)
    : m_true(mask_true.as_uint())
    , m_false(mask_false.as_uint())
{
    if (m_true & m_false)
	throw std::runtime_error
	    (fmt::format("tribool: cannot be both true and false: {:b} {:b} ==> {:b}",
			 mask_true.as_uint(), mask_false.as_uint(), m_true & m_false));
}

tribool32& tribool32::operator&=(tribool32 b) {
    auto t = is_true() & b.is_true();
    auto f = is_false() | b.is_false();
    return *this = {t, f};
}

tribool32& tribool32::operator|=(tribool32 b) {
    auto t = is_true() | b.is_true();
    auto f = is_false() & b.is_false();
    return *this = {t, f};
}

tribool32& tribool32::operator^=(tribool32 b) {
    auto t = (is_true() & b.is_false()) |
	(is_false() & b.is_true());
    auto f = (is_true() & b.is_true()) |
	(is_false() & b.is_false());
    return *this = {t, f};
}

tribool32& tribool32::operator+=(tribool32 b) {
    if (is_known().all() and b.is_known().all())
	*this = tribool32{bool32{m_true + b.m_true}};
    else
	*this = tribool32{};
    return *this;
}

tribool32& tribool32::operator-=(tribool32 b) {
    if (is_known().all() and b.is_known().all())
	*this = tribool32{bool32{m_true - b.m_true}};
    else
	*this = tribool32{};
    return *this;
}

tribool32& tribool32::operator<<(tribool32 b) {
    m_true |= ~m_false & b.m_true;
    m_false |= ~m_true & b.m_false;
    return *this;
}

tribool32& tribool32::operator<<=(tribool32 b) {
    m_true &= ~b.m_false;
    m_true |= b.m_true;
    m_false &= ~b.m_true;
    m_false |= b.m_false;
    return *this;
}

tribool32 operator~(tribool32 a) {
    auto t = a.is_false();
    auto f = a.is_true();
    return {t, f};
}

tribool32 operator&(tribool32 a, tribool32 b) {
    return a &= b;
}

tribool32 operator|(tribool32 a, tribool32 b) {
    return a |= b;
}

tribool32 operator^(tribool32 a, tribool32 b) {
    return a ^= b;
}

tribool32 operator+(tribool32 a, tribool32 b) {
    return a += b;
}

tribool32 operator-(tribool32 a, tribool32 b) {
    return a -= b;
}

tribool32 rotr(tribool32 a, uint n) {
    auto t = std::rotr(a.is_true().as_uint(), n);
    auto f = std::rotr(a.is_false().as_uint(), n);
    return {t, f};
}

bool any(tribool32 a) {
    return a.any();
}

bool all(tribool32 a) {
    return a.all();
}

bool none(tribool32 a) {
    return a.none();
}

tribool32 operator>>(tribool32 a, uint n) {
    auto t = a.is_true() >> n;
    auto f = a.is_false() >> n;
    return {t, f};
}

std::ostream& operator<<(std::ostream& os, tribool32 value) {
    for (auto i = 0; i < 32; ++i)
	os << value[i];
    return os;
}

}; // type
}; // core
