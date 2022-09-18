// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/sbs/concept.h"

template<class T, class U>
void to_sbs(std::ostream& os, const std::pair<T,U>& pair);

template<class T, class U>
void from_sbs(std::istream& is, std::pair<T,U>& pair);
