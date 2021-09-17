// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/pod_decl.h"

template<class T>
requires core::sbs::PodLike<T>
void to_sbs(std::ostream& os, const T& value) {
    os.write((char*)&value, sizeof(value));
}

template<class T>
requires core::sbs::PodLike<T>
void from_sbs(std::istream& is, T& value) {
    is.read((char*)&value, sizeof(value));
}

template<class T>
requires core::sbs::PodLike<T>
void to_sbs(std::ostream& os, T *data, size_t count) {
    os.write((char*)data, count * sizeof(T));
}

template<class T>
requires core::sbs::PodLike<T>
void from_sbs(std::istream& is, T *data, size_t count) {
    is.read((char*)data, count * sizeof(T));
}

