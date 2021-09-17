// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include "core/bit/sbs/concept.h"

void to_sbs(std::ostream& os, const string& str);
void from_sbs(std::istream& is, string& str);
