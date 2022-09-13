// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace core {
inline namespace util {
       
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
    unsigned_real(double x = 0.0)
	: value(x) {
	validate();
    }

    operator double() const { return value; }
    
    unsigned_real operator+() const { return *this; }
    unsigned_real operator-() const { return unsigned_real{-value}; }

private:
    void validate();
    
    double value;
};

// Convert the **unsigned_real** `value` into the **json** `j`.
void to_json(json& j, unsigned_real value);

// Convert the **json** `j` into the **unsigned_real** `value`.
void from_json(const json& j, unsigned_real& value);


using ureal = unsigned_real;

inline ureal operator+(ureal a, ureal b) { return (double)a + (double)b; }
inline double operator+(ureal a, double b) { return (double)a + b; }
inline double operator+(double a, ureal b) { return a + (double)b; }

inline ureal operator-(ureal a, ureal b) { return (double)a - (double)b; }
inline double operator-(ureal a, double b) { return (double)a - b; }
inline double operator-(double a, ureal b) { return a - (double)b; }

inline ureal operator*(ureal a, ureal b) { return (double)a * (double)b; }
inline double operator*(ureal a, double b) { return (double)a * b; }
inline double operator*(double a, ureal b) { return a * (double)b; }

inline ureal operator/(ureal a, ureal b) { return (double)a / (double)b; }
inline double operator/(ureal a, double b) { return (double)a / b; }
inline double operator/(double a, ureal b) { return a / (double)b; }

}; // util
}; // core

