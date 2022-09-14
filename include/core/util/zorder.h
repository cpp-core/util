// Copyright (C) 2022 by Mark Melton
//

#pragma once
#include <cstdint>
#include <tuple>

// Return the z-order encoding of the three given dimensions **a**,
// **b** and **c**. Each dimension can have up to 21-bits of data
// which produces a 63 bit code.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
std::uint64_t zorder64_encode3(std::uint32_t a, std::uint32_t b, std::uint32_t c);

// Return the original three dimensions represented by the z-order
// encoding **code**. The given **code** may contains up to 63 bits of
// data producing three dimensions with up to 21 bits of data each.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
std::tuple<std::uint32_t,std::uint32_t,std::uint32_t> zorder64_decode3(std::uint64_t code);

// Return the z-order encoding of the three given dimensions **a**,
// **b** and **c**. Each dimension can have up to 10-bits of data
// which produces a 30 bit code.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
std::uint32_t zorder32_encode3(std::uint16_t a, std::uint16_t b, std::uint16_t c);

// Return the original three dimensions represented by the z-order
// encoding **code**. The given **code** may contains up to 30 bits of
// data producing three dimensions with up to 10 bits of data each.
//
// Z-order (Lebsegue, or Morton) encoding maps multiple dimensions
// into one while preserving locality by interleaving the bits from
// each dimension.
std::tuple<std::uint16_t,std::uint16_t,std::uint16_t> zorder32_decode3(std::uint32_t code);
