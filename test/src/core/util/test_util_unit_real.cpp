// Copyright (C) 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "core/util/unit_real.h"
#include "coro/stream/stream.h"

static const int NumberSamples = 64;

using namespace coro;
using namespace core::util;
using json = nlohmann::json;

TEST(UnitReal, Construct)
{
    for (auto value : sampler<double>(0, 1) | take(NumberSamples)) {
	unit_real x{value};
	EXPECT_EQ(x, value);
    }
}

TEST(UnitReal, ConstructThrow)
{
    for (auto value : sampler<double>(-1, 0) | take(NumberSamples))
	EXPECT_THROW(unit_real{value}, std::runtime_error);

    for (auto value : sampler<double>(1, 2) | take(NumberSamples))
	EXPECT_THROW(unit_real{value}, std::runtime_error);
}

TEST(UnitReal, Quantize)
{
    for (auto value : sampler<double>(0, 1) | take(NumberSamples)) {
	unit_real x{value};
	auto q = x.quantize(60);
	auto y = q / double(1ul << 60);
	auto diff = (double)x - y;
	EXPECT_LT(diff, 1e-12);
    }    
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
