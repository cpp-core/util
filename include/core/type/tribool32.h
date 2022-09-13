// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <compare>
#include "core/type/tribool.h"
#include "core/type/bool32.h"

namespace core {
inline namespace type {
       
class tribool32 {
public:
    class reference {
    public:
	reference();
	reference(std::uint32_t *ptr_true, std::uint32_t *ptr_false, std::uint32_t mask);
	reference& operator=(tribool x) noexcept;
	reference& operator=(const reference& x) noexcept;
	operator tribool() const noexcept;
    private:
	std::uint32_t *m_ptr_true, *m_ptr_false;
	std::uint32_t m_mask;
    };

    using Value = std::uint32_t;

    // Construct a tribool32 with all underling tribools indeterminate.
    tribool32();

    // Construct a tribool32 with all underlying tribools set to <value>.
    explicit tribool32(bool value);

    // Construct a tribool32 with the underlying tribools coresponding
    // to the bits in <value>.
    explicit tribool32(std::uint32_t value);

    // Construct a tribool32 with the underlying tribools coresponding
    // to the underlying bools in <value>.
    explicit tribool32(bool32 value);

    // Construct a tribool32 with <mask_true> underlying tribools set
    // to true, <mask_false> underlying tribools set to false, and the
    // remaining set to indeterminate.
    tribool32(std::uint32_t mask_true, std::uint32_t mask_false);

    // Construct a tribool32 with <mask_true> underlying tribools set
    // to true, <mask_false> underlying tribools set to false, and the
    // remaining set to indeterminate.
    tribool32(bool32 mask_true, bool32 mask_false);

    // Return the tribool at index <n>.
    const tribool at(size_t n) const {
	return tribool{bool(m_true & (1 << n)), bool(m_false & (1 << n))};
    }

    // Return the tribool at index <n>.
    const tribool operator[](size_t n) const { return at(n); }

    // Return a proxy reference to the tribool at index <n>.
    reference operator[](size_t n) { return reference{&m_true, &m_false, 1u << n}; }

    // Return true iff the n'th tribool is true.
    bool is_true(size_t n) const { return m_true & (1 << n); }

    // Return true iff the n'th tribool is false.
    bool is_false(size_t n) const { return m_false & (1 << n); }

    // Return true iff the n'th tribool it not indeterminate.
    bool is_known(size_t n) const { return (m_true | m_false) & (1 << n); }

    // Return true iff the n'th tribool it indeterminate.
    bool is_unknown(size_t n) const { return not is_known(n); }

    // Return a bool32 representing the true tribools.
    bool32 is_true() const { return m_true; }

    // Return a bool32 representing the false tribools.
    bool32 is_false() const { return m_false; }

    // Return a bool32 representing the known tribools.
    bool32 is_known() const { return m_false | m_true; }

    // Return a bool32 representing the unknown tribools.
    bool32 is_unknown() const { return ~is_known(); }

    // Return true iff any of the underlying tribools are true.
    bool any() const { return m_true; }

    // Return true iff all of the underlying tribools are true.
    bool all() const { return m_true == ~Value{0}; }

    // Return true iff none of the underlying tribools are true.
    bool none() const { return m_true == 0; }

    // Update and return the underlying tribools with the logical and of <other>.
    tribool32& operator&=(tribool32 other);

    // Update and return the underlying tribools with the logical or of <other>.
    tribool32& operator|=(tribool32 other);

    // Update and return the underlying tribools with the logical xor of <other>.
    tribool32& operator^=(tribool32 other);

    // Update and return the sum with <other> modulo 2^32 interpreting
    // the underlying tribools as unsigned integers.
    tribool32& operator+=(tribool32 other);

    // Update and return the difference with <other> modulo 2^32
    // interpreting the underlying tribools as unsigned integers.
    tribool32& operator-=(tribool32 other);

    // Update and return with <other> any underlying tribools that are
    // indeterminate.
    tribool32& operator<<(tribool32 other);

    // Update and return with <other> where any <other> underlying
    // tribools are not indeterminate.
    tribool32& operator<<=(tribool32 other);

    std::strong_ordering operator<=>(const tribool32& other) const = default;

private:
    Value m_true{0};
    Value m_false{0};
};

using tribool32s = std::vector<tribool32>;

std::ostream& operator<<(std::ostream& os, tribool32 a);

// Return the complement of <a> for the underlying tribools.
tribool32 operator~(tribool32 a);

// Return <a> and <b> for the underlying tribools.
tribool32 operator&(tribool32 a, tribool32 b);

// Return <a> or <b> for the underlying tribools.
tribool32 operator|(tribool32 a, tribool32 b);

// Return <a> xor <b> for the underlying tribools.
tribool32 operator^(tribool32 a, tribool32 b);

// Return <a> + <b> using modulo 2^32 arithmetic interpreting the
// underlying tribools and an unsigned integer.
tribool32 operator+(tribool32 a, tribool32 b);

// Return <a> - <b> using modulo 2^32 arithmetic interpreting the
// underlying tribools and an unsigned integer.
tribool32 operator-(tribool32 a, tribool32 b);

// Return the underlying tribools in <a> rotated right <n> positions.
tribool32 rotr(tribool32 a, uint n);

// Return the underlying tribools in <a> shifted right <n> positions.
tribool32 operator>>(tribool32 a, uint n);

// Return true if any of the underlying tribools are true.
bool any(tribool32 a);

// Return true if all of the underlying tribools are true.
bool all(tribool32 a);

// Return true if none of the underlying tribools are true.
bool none(tribool32 a);

}; // type
}; // core
