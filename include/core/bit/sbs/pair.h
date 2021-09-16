// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/standard.h"

template<class T, class U>
void to_sbs(std::ostream& os, const std::pair<T,U>& pair) {
    to_sbs(os, pair.first);
    to_sbs(os, pair.second);
}

template<class T, class U>
void from_sbs(std::istream& is, std::pair<T,U>& pair) {
    from_sbs(is, pair.first);
    from_sbs(is, pair.second);
}
