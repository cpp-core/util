// Copyright (C) 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

// Return the z-order encoding of the three given dimensions **a**,
// **b** and **c**. Each dimension can have up to 21-bits of data
// which produces a 63 bit code.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
uint64 zorder64_encode3(uint32 a, uint32 b, uint32 c);

// Return the original three dimensions represented by the z-order
// encoding **code**. The given **code** may contains up to 63 bits of
// data producing three dimensions with up to 21 bits of data each.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
std::tuple<uint32,uint32,uint32> zorder64_decode3(uint64 code);

// Return the z-order encoding of the three given dimensions **a**,
// **b** and **c**. Each dimension can have up to 10-bits of data
// which produces a 30 bit code.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
uint32 zorder32_encode3(uint16 a, uint16 b, uint16 c);

// Return the original three dimensions represented by the z-order
// encoding **code**. The given **code** may contains up to 30 bits of
// data producing three dimensions with up to 10 bits of data each.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
std::tuple<uint16,uint16,uint16> zorder32_decode3(uint32 code);
