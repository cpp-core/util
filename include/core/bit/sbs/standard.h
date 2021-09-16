// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/concept.h"

// For mem-copyable types, write/read the object bytes to/from the
// stream.
template<class T>
requires core::sbs::MemCopyable<T>
void to_sbs(std::ostream& os, const T& value) {
    os.write((char*)&value, sizeof(value));
}

template<class T>
requires core::sbs::MemCopyable<T>
void from_sbs(std::istream& is, T& value) {
    is.read((char*)&value, sizeof(value));
}

// For contiguous array of mem-copyable types, write/read the bytes
// directly to/from memory.
template<class T>
requires core::sbs::MemCopyable<T>
void to_sbs(std::ostream& os, T *data, size_t count) {
    os.write((char*)data, count * sizeof(T));
}

template<class T>
requires core::sbs::MemCopyable<T>
void from_sbs(std::istream& is, T *data, size_t count) {
    is.read((char*)data, count * sizeof(T));
}

