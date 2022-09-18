// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/sbs/concept.h"

// For mem-copyable types, write/read the object bytes to/from the
// stream.
template<class T>
requires core::sbs::PodLike<T>
void to_sbs(std::ostream& os, const T& value);

template<class T>
requires core::sbs::PodLike<T>
void from_sbs(std::istream& is, T& value);

// For contiguous array of mem-copyable types, write/read the bytes
// directly to/from memory.
template<class T>
requires core::sbs::PodLike<T>
void to_sbs(std::ostream& os, T *data, size_t count);

template<class T>
requires core::sbs::PodLike<T>
void from_sbs(std::istream& is, T *data, size_t count);
