// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/extra/json/nljson.h"

namespace core {
inline namespace type {
       
// The **unsigned_real** class models the concept of a non-negative
// real-valued quantity. The goal is transparent interoperability with
// standard `real` quantities.
//
// > Invariants
// 1. Non-negative
struct unsigned_real {
    // Construct a **positive_real** from the supplied value `x`.
    //
    // `param:` *x* Positive real value.
    // `except:` *runtime_error* If x is negative.
    unsigned_real(real x = 0.0)
	: value(x) {
	validate();
    }

    operator real() const { return value; }
    
    unsigned_real operator+() const { return *this; }
    unsigned_real operator-() const { return unsigned_real{-value}; }

private:
    void validate();
    
    real value;
};

// Convert the **unsigned_real** `value` into the **json** `j`.
void to_json(json& j, unsigned_real value);

// Convert the **json** `j` into the **unsigned_real** `value`.
void from_json(const json& j, unsigned_real& value);


using ureal = unsigned_real;

inline ureal operator+(ureal a, ureal b) { return (real)a + (real)b; }
inline real operator+(ureal a, real b) { return (real)a + b; }
inline real operator+(real a, ureal b) { return a + (real)b; }

inline ureal operator-(ureal a, ureal b) { return (real)a - (real)b; }
inline real operator-(ureal a, real b) { return (real)a - b; }
inline real operator-(real a, ureal b) { return a - (real)b; }

inline ureal operator*(ureal a, ureal b) { return (real)a * (real)b; }
inline real operator*(ureal a, real b) { return (real)a * b; }
inline real operator*(real a, ureal b) { return a * (real)b; }

inline ureal operator/(ureal a, ureal b) { return (real)a / (real)b; }
inline real operator/(ureal a, real b) { return (real)a / b; }
inline real operator/(real a, ureal b) { return a / (real)b; }

}; // type
}; // core

