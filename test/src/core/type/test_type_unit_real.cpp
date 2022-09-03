// Copyright (C) 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/type/unit_real.h"
#include "coro/stream/stream.h"

static const int NumberSamples = 64;

using namespace coro;
using namespace core::type;

TEST(UnitReal, Construct)
{
    for (auto value : sampler<real>(0, 1) | take(NumberSamples)) {
	unit_real x{value};
	EXPECT_EQ(x, value);
    }
}

TEST(UnitReal, ConstructThrow)
{
    for (auto value : sampler<real>(-1, 0) | take(NumberSamples))
	EXPECT_THROW(unit_real{value}, core::runtime_error);

    for (auto value : sampler<real>(1, 2) | take(NumberSamples))
	EXPECT_THROW(unit_real{value}, core::runtime_error);
}

TEST(UnitReal, Quantize)
{
    for (auto value : sampler<real>(0, 1) | take(NumberSamples)) {
	unit_real x{value};
	auto q = x.quantize(60);
	auto y = q / real(1ul << 60);
	EXPECT_EQ((real)x, y);
    }    
}

// TEST(UnsignedReal, ToFromJson)
// {
//     for (auto a : sampler<real>(0, 1) | take(NumberSamples)) {
// 	ureal x{a};
// 	json j = x;
// 	auto y = j.get<ureal>();
// 	EXPECT_EQ(x, y);
//     }
// }

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
