// Copyright (C) 2017, 2019, 2022 by Mark Melton
//

#include "core/util/random.h"

namespace core
{

static std::mt19937 gs_rng;

std::mt19937& rng() { return gs_rng; }

};
