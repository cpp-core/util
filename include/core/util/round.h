// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once

// floor
//
// rounds x down to the nearest precision increment shifted down by bias.
//
// floor(100.054, 0.05, 0.00) --> 100.05
// floor(100.054, 0.05, 0.01) --> 100.01
//
double floor(double x, double precision, double bias = 0.0);

// ceil
//
// rounds x up to the nearest precision increment shifted up by bias.
//
// ceil(100.044, 0.05, 0.00) --> 100.05
// ceil(100.044, 0.05, 0.01) --> 100.09
double ceil(double x, double precision, double bias = 0.0);

