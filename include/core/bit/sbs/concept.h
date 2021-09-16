// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/common.h"

namespace core::sbs
{

// Concept for container like types.
template<class T>
concept Container = requires(T a) {
    typename T::value_type;
    typename T::size_type;
    { a.begin() };
    { a.end() };
};

// Concept for container like types that store elements contiguously
// in memory.
template<class T>
concept ContiguousContainer = requires(T a) {
    requires Container<T>;
    { a.data() };
    { a.size() };
};

// Concept for container like types that do not store elements
// contiguously in memory.
template<class T>
concept NonContiguousContainer = Container<T> and not ContiguousContainer<T>;

// Concept for mem-copyable types (formerly pod types)
template<class T>
concept MemCopyable = requires(T a) {
    std::is_standard_layout_v<T>;
};

}; // core::sbs

