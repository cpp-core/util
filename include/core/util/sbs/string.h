// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/util/sbs/string_decl.h"
#include "core/util/sbs/pod_decl.h"

inline void to_sbs(std::ostream& os, const std::string& str) {
    to_sbs(os, str.size());
    to_sbs(os, &str[0], str.size());
}

inline void from_sbs(std::istream& is, std::string& str) {
    size_t count;
    from_sbs(is, count);
    str.resize(count);
    from_sbs(is, &str[0], str.size());
}
