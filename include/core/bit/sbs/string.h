// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/string_decl.h"
#include "core/bit/sbs/pod_decl.h"

void to_sbs(std::ostream& os, const string& str) {
    to_sbs(os, str.size());
    to_sbs(os, &str[0], str.size());
}

void from_sbs(std::istream& is, string& str) {
    size_t count;
    from_sbs(is, count);
    str.resize(count);
    from_sbs(is, &str[0], str.size());
}
