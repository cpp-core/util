// Copyright (C) 2021 by Mark Melton
//

#include "core/hash/combine.h"
#include "core/hash/hasher.h"

namespace core {

// hash - return hash of arguments
template<class... Args>
size_t hash(Args&&... args) {
    size_t v{0};
    (detail::combine(v, detail::hasher<std::decay_t<Args>>()(std::forward<Args>(args))),...);
    return v;
}

}; // core

