// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <compare>
#include <optional>

namespace core {
inline namespace util {
       
class tribool {
public:
    // Construct an indeterminate tribool
    tribool() { }
    
    // Construct an indeterminate tribool
    tribool(const std::nullopt_t) { }
    
    // Construct a tribool that is either true or values depending on
    // <value>.
    explicit tribool(bool value) : m_value(value) { }

    // Construct a tribool that is true if <is_true>, is false if
    // <is_fasle>, is indeterminate otherwise.
    explicit tribool(bool is_true, bool is_false);

    // Return true iff value is known, false otherwise.
    operator bool() { return (bool)m_value; }
    
    // Return true iff value is known, false otherwise.
    bool is_known() const { return (bool)m_value; }

    // Return true iff value is true.
    bool is_true() const { return is_known() && bool_value(); }
    
    // Return true iff value is false.
    bool is_false() const { return is_known() && not bool_value(); }

    // Return the boolean value, undefined if indeterminate.
    bool bool_value() const { return m_value.value(); }

    // Reset value to indeterminate.
    void clear() { m_value = std::nullopt; }

    // Update this value with the logical conjunction of <other>.
    tribool& operator&=(tribool other);

    // Update this value with the logical disjunction of <other>.
    tribool& operator|=(tribool other);

    // Update this value with the logical exclusive disjunction of <other>.
    tribool& operator^=(tribool other);

    // Update this value with the sum of <other> using modulo 2 arithmetic.
    tribool& operator+=(tribool other);

    // Update this value with the difference of <other> using modulo 2 arithmetic.
    tribool& operator-=(tribool other);

    // If indeterminate, set this value to <other>.
    tribool& operator<<(tribool other);

    // If other is not indeterminate, set this value to <other>.
    tribool& operator<<=(tribool other);
    
    std::strong_ordering operator<=>(const tribool&) const = default;
private:
    std::optional<bool> m_value;
};

std::ostream& operator<<(std::ostream& os, const tribool& value);

// Return the logical negation of this value.
tribool operator~(tribool a);
    
// Return <a> and <b>.
tribool operator&(tribool a, tribool b);

// Return <a> or <b>.
tribool operator|(tribool a, tribool b);

// Return <a> xor <b>.
tribool operator^(tribool a, tribool b);

// Return <a> + <b> using modulo 2 arithmetic interpreting the tribool
// as a single bit.
tribool operator+(tribool a, tribool b);

// Return <a> - <b> using modulo 2 arithmetic interpreting the tribool
// as a single bit.
tribool operator-(tribool a, tribool b);

// Return true if any of the underlying bools are true.
bool any(tribool a);

// Return true if all of the underlying bools are true.
bool all(tribool a);

// Return true if none of the underlying bools are true.
bool none(tribool a);

}; // type
}; // core
