// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <utility>
#include "core/util/hash/combine.h"

namespace core {

namespace hasher {

template<class T>
struct Hash;

};


// hash - return hash of arguments
template<class... Args>
std::uint64_t hash(Args&&... args) {
    std::uint64_t v{0};
    (detail::combine(v, hasher::Hash<std::decay_t<Args>>()(std::forward<Args>(args))),...);
    return v;
}

}; // core

