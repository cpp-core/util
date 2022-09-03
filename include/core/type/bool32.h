// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <compare>
#include "core/util/common.h"

namespace core {
inline namespace type {
       
// Compact representation of 32 underlying bools.
class bool32 {
public:
    class reference {
    public:
	reference();
	reference(uint32 *ptr, uint32 mask);
	reference& operator=(bool x) noexcept;
	constexpr reference& operator=(const reference& x) noexcept { return *this = bool(x); }
	constexpr operator bool() const noexcept { return bool(*m_ptr & m_mask); }
	constexpr void flip() noexcept { *m_ptr = *m_ptr ^ m_mask; }
    private:
	uint32 *m_ptr;
	uint32 m_mask;
    };

    // Construct a bool32 with all underlying bools set to <value>.
    explicit bool32(bool value) : m_value(value ? ~uint32{0} : 0) { }

    // Construct a bool32 with the underlying bools set to the bits in <value>.
    bool32(uint32 value = 0) : m_value(value) { }

    // Return the underlying unsigned integer.
    uint32 as_uint() const { return m_value; }

    // Return the bool at index <n>.
    bool at(size_t index) const { return m_value & (1u << index); }

    // Return the bool at index <n>.
    bool operator[](size_t index) const { return at(index); }

    // Return a proxy reference to the bool at index <n>.
    reference operator[](size_t index) { return reference(&m_value, 1u << index); }

    // Return true if any underlying bools are true.
    bool any() const { return m_value; }

    // Return true if all underlying bools are true.
    bool all() const { return m_value == ~uint32{0}; }

    // Return true if no underlying bools are true.
    bool none() const { return m_value == 0; }

    // Update and return the underlying bools with the logical and of <other>.
    bool32& operator&=(bool32 other);

    // Update and return the underlying bools with the logical or of <other>.
    bool32& operator|=(bool32 other);

    // Update and return the underlying bools with the logical xor of <other>.
    bool32& operator^=(bool32 other);

    // Update and return the sum with <other> modulo 2^32 interpreting
    // the underlying bools as unsigned integers.
    bool32& operator+=(bool32 other);

    // Update and return the difference with <other> modulo 2^32
    // interpreting the underlying bools as unsigned integers.
    bool32& operator-=(bool32 other);

    std::strong_ordering operator<=>(const bool32&) const = default;
    
private:
    uint32 m_value;
};

using bool32s = vector<bool32>;

std::ostream& operator<<(std::ostream& os, bool32 a);

// Return ~<a> for the underlying bools.
bool32 operator~(bool32 a);

// Return <a> and <b> for the underlying bools.
bool32 operator&(bool32 a, bool32 b);

// Return <a> or <b> for the underlying bools.
bool32 operator|(bool32 a, bool32 b);

// Return <a> xor <b> for the underlying bools.
bool32 operator^(bool32 a, bool32 b);

// Return <a> + <b> treating the underlying bools and unsigned
// integers.
bool32 operator+(bool32 a, bool32 b);

// Return <a> - <b> treating the underlying bools and unsigned
// integers.
bool32 operator-(bool32 a, bool32 b);

// Return <a> rotated right <n> positions for the underlying bools.
bool32 rotr(bool32 a, uint n);

// Return <a> shifted right <b> positions for the underlying bools.
bool32 operator>>(bool32 a, uint n);

// Return true if any of the underlying bools are true.
bool any(bool32 a);

// Return true if all of the underlying bools are true.
bool all(bool32 a);

// Return true if none of the underlying bools are true.
bool none(bool32 a);

}; // type
}; // core
