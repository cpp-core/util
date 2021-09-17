// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/concept.h"

template<class T>
requires core::sbs::SequenceContainer<T>
void to_sbs(std::ostream& os, const T& container);

template<class T>
requires core::sbs::SequenceContainer<T>
void from_sbs(std::istream& is, T& container);
