// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include "core/type/tribool.h"

namespace core {
inline namespace type {
       
tribool::tribool(bool is_true, bool is_false)
{
    if (is_true) m_value = true;
    else if (is_false) m_value = false;
    else m_value = std::nullopt;
}

tribool& tribool::operator&=(tribool b) {
    if (is_false() or b.is_false()) *this = tribool{false};
    else if (is_true() and b.is_true()) *this = tribool{true};
    else *this = tribool{};
    return *this;
}

tribool& tribool::operator|=(tribool b) {
    if (is_false() and b.is_false()) *this = tribool{false};
    else if (is_true() or b.is_true()) *this = tribool{true};
    else *this = tribool{};
    return *this;
}

tribool& tribool::operator^=(tribool b) {
    if (not is_known() or not b.is_known()) *this = tribool{};
    else if (bool_value() == b.bool_value()) *this = tribool{false};
    else *this = tribool{true};
    return *this;
}

tribool& tribool::operator+=(tribool b) {
    return *this ^= b;
}

tribool& tribool::operator-=(tribool b) {
    return *this ^= b;
}

tribool operator~(tribool a) {
    if (not a.is_known()) return tribool{};
    else return tribool{not a.bool_value()};
}

tribool operator&(tribool a, tribool b) {
    return a &= b;
}

tribool operator|(tribool a, tribool b) {
    return a |= b;
}

tribool operator^(tribool a, tribool b) {
    return a ^= b;
}

tribool operator+(tribool a, tribool b) {
    return a += b;
}

tribool operator-(tribool a, tribool b) {
    return a -= b;
}

tribool& tribool::operator<<(tribool other) {
    if (not is_known())
	*this = other;
    return *this;
}

tribool& tribool::operator<<=(tribool other) {
    if (other.is_known())
	*this = other;
    return *this;
}

bool any(tribool a) {
    return a.is_true();
}

bool all(tribool a) {
    return a.is_true();
}

bool none(tribool a) {
    return not a.is_true();
}

std::ostream& operator<<(std::ostream& os, const tribool& value) {
    if (not value.is_known())
	return os << '?';

    bool alpha = os.flags() & os.boolalpha;
    if (value.is_true())
	return os << (alpha ? "t" : "1");
    
    return os << (alpha ? "f" : "0");
}

}; // type
}; // core
