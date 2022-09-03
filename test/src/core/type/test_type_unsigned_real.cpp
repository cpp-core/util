// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/type/unsigned_real.h"
#include "coro/stream/stream.h"

static const int NumberSamples = 32;

using namespace coro;
using namespace core::type;

TEST(UnsignedReal, Construct)
{
    for (auto value : sampler<real>(0, 1) | take(NumberSamples)) {
	ureal x{value};
	EXPECT_EQ(x, value);
    }
}

TEST(UnsignedReal, ConstructThrow)
{
    for (auto value : sampler<real>(-1, 0) | take(NumberSamples)) {
	EXPECT_THROW(ureal{value}, core::runtime_error);
    }
}

TEST(UnsignedReal, Arithmetic)
{
    for (auto [a, b] : sampler<real>(0, 1) | group_tuple<2>() | take(NumberSamples)) {
	ureal x{a + b}, y{b};
	EXPECT_EQ(+x, x);
	EXPECT_EQ(typeid(+x), typeid(ureal));
	
	EXPECT_EQ(x + y, ureal{x + y});
	EXPECT_EQ(typeid(x + y), typeid(ureal));
	
	EXPECT_EQ(x - y, ureal{x - y});
	EXPECT_EQ(typeid(x - y), typeid(ureal));
	
	EXPECT_EQ(x * y, ureal{x * y});
	EXPECT_EQ(typeid(x * y), typeid(ureal));
	
	EXPECT_EQ(x / y, ureal{x / y});
	EXPECT_EQ(typeid(x / y), typeid(ureal));
    }
}

TEST(UnsignedReal, ArithmeticInterop)
{
    for (auto [a, b] : sampler<real>(0, 1) | group_tuple<2>() | take(NumberSamples)) {
	real x{a + b}, y{b};
	ureal ux{x};

	EXPECT_EQ(ux + y, x + y);
	EXPECT_EQ(y + ux, x + y);
	EXPECT_EQ(typeid(x + y), typeid(real));
	EXPECT_EQ(typeid(y + x), typeid(real));
	
	EXPECT_EQ(ux - y, x - y);
	EXPECT_EQ(y - ux, y - x);
	EXPECT_EQ(typeid(ux - y), typeid(real));
	EXPECT_EQ(typeid(y - ux), typeid(real));
	
	EXPECT_EQ(ux * y, x * y);
	EXPECT_EQ(y * ux, y * x);
	EXPECT_EQ(typeid(ux * y), typeid(real));
	EXPECT_EQ(typeid(y * ux), typeid(real));
	
	EXPECT_EQ(ux / y, x / y);
	EXPECT_EQ(y / ux, y / x);
	EXPECT_EQ(typeid(ux / y), typeid(real));
	EXPECT_EQ(typeid(y / ux), typeid(real));
    }
}

TEST(UnsignedReal, ToFromJson)
{
    for (auto a : sampler<real>(0, 1) | take(NumberSamples)) {
	ureal x{a};
	json j = x;
	auto y = j.get<ureal>();
	EXPECT_EQ(x, y);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
