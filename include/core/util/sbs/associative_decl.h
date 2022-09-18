// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/sbs/concept.h"

template<class T>
requires core::sbs::AssociativeContainer<T>
void to_sbs(std::ostream& os, const T& container);

template<class T>
requires core::sbs::AssociativeContainer<T>
void from_sbs(std::istream& is, T& container);
