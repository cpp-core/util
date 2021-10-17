// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/hash/combine.h"
#include "core/hash/hasher.h"

namespace core {

// hash - return hash of arguments
template<class... Args>
uint64 hash(Args&&... args) {
    uint64 v{0};
    (detail::combine(v, detail::hasher<std::decay_t<Args>>()(std::forward<Args>(args))),...);
    return v;
}

}; // core

