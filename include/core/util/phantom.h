// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace core {
inline namespace util {
       
// CRTP mixin providing std::ostream output and json conversion to
// improve the ergonomics of creating and using phantom types
// (i.e. types that are only used at compile time to constrain the
// valid programs and have no impact at runtime).
//
// struct Name : public Phantom<std::string> { };
// Name foo{"abc"s};
// cout << foo << endl;
// json j = foo;
// auto bar = j.get<Name>();
//
template<class T>
class Phantom {
public:
    // Construct a Phantom with default intialization of the value.
    Phantom() {}

    // Construct a Phantom initialized to value.
    Phantom(const T& value)
	: value_(value) {
    }
    
    // Construct a Phantom initialized to value.
    Phantom(T&& value)
	: value_(std::forward<T>(value)) {
    }

    // Construct a Phantom from const char* if T is std::string. This
    // is strictly for convenience.
    template<class U = T>
    requires std::is_same_v<std::string, U>
    Phantom(const char *str)
	: value_(str) {
    }

    // Comparison to T
    bool operator==(const T& other) { return value() == other; }

    // Allow automagical conversion to T.
    operator T() const { return value_; }

    // Direct access to the underlying value.
    T& value() { return value_; }
    
    // Direct access to the underlying value.
    const T& value() const { return value_; }

private:
    T value_;
};

// Output Phantom<T> to std::ostream
template<class T>
std::ostream& operator<<(std::ostream& os, const Phantom<T>& phantom) {
    os << phantom.value();
    return os;
}

// Convert Phantom<T> to json. The underlying T must be convertible to
// json.
template<class T>
void to_json(json& j, const Phantom<T>& phantom) {
    j = phantom.value();
}

// Convert json to Phantom<T>. The underlying T must be convertible
// from json.
template<class T>
void from_json(const json& j, Phantom<T>& phantom) {
    phantom = j.get<T>();
}

}; // type
}; // core
