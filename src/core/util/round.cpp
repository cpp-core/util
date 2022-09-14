// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#include <cmath>
#include "core/util/round.h"

double floor(double x, double precision, double bias)
{
    return std::floor((x - bias) / precision) * precision + bias;
}

double ceil(double x, double precision, double bias)
{
    return std::ceil((x + bias) / precision) * precision - bias;
}

