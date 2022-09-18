// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include "core/bit/sbs/concept.h"

void to_sbs(std::ostream& os, const std::string& str);
void from_sbs(std::istream& is, std::string& str);
