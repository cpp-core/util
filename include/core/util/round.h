// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

// floor
//
// rounds x down to the nearest precision increment shifted down by bias.
//
// floor(100.054, 0.05, 0.00) --> 100.05
// floor(100.054, 0.05, 0.01) --> 100.01
//
real floor(real x, real precision, real bias = 0.0);

// ceil
//
// rounds x up to the nearest precision increment shifted up by bias.
//
// ceil(100.044, 0.05, 0.00) --> 100.05
// ceil(100.044, 0.05, 0.01) --> 100.09
real ceil(real x, real precision, real bias = 0.0);

