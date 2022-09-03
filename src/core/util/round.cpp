// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#include <cmath>
#include "core/util/round.h"

real floor(real x, real precision, real bias)
{
    return std::floor((x - bias) / precision) * precision + bias;
}

real ceil(real x, real precision, real bias)
{
    return std::ceil((x + bias) / precision) * precision - bias;
}

