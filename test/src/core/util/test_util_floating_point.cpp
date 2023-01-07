// Copyright 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "coro/stream/stream.h"
#include "core/util/floating_point.h"

using namespace coro;

TEST(FloatingPoint, ToIntegerExponent)
{
    for (auto x : sampler<double>(-1e10, 1e10) | take(1024)) {
	auto [n, e] = core::fp_to_integer_exponent(x);
	EXPECT_EQ(core::integer_exponent_to_fp(n, e), x);
    }
}

TEST(FloatingPoint, Normalized)
{
    for (auto a : log_sampler<int64_t>() | take(1024)) {
	double x(a);
	auto [n, e] = core::fp_to_integer_exponent(x);
	EXPECT_GE(e, 0);
	EXPECT_EQ(core::integer_exponent_to_fp(n, e), x);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
