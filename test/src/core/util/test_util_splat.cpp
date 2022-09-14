// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/splat.h"

TEST(Splat, OneElement)
{
    std::vector<double> x{1.0};
    auto [x0] = splat(x, 0);
    EXPECT_EQ(x0, 1.0);
    EXPECT_THROW(splat(x, -1), core::runtime_error);
    EXPECT_THROW(splat(x, 1), core::runtime_error);
}

TEST(Splat, TwoElement)
{
    std::vector<double> x{1.0, 2.0};
    {
	auto [x0] = splat(x, 0);
	EXPECT_EQ(x0, 1.0);
    }
    {
	auto [x0, x1] = splat(x, 0, 1);
	EXPECT_EQ(x0, 1.0);
	EXPECT_EQ(x1, 2.0);
    }
    {
	auto [x1, x0] = splat(x, 1, 0);
	EXPECT_EQ(x0, 1.0);
	EXPECT_EQ(x1, 2.0);
    }
    EXPECT_THROW(splat(x, -1), core::runtime_error);
    EXPECT_THROW(splat(x, 2), core::runtime_error);
}

TEST(Splat, ThreeElement)
{
    std::vector<double> x{1.0, 2.0, 3.0};
    {
	auto [x0] = splat(x, 0);
	EXPECT_EQ(x0, 1.0);
    }
    {
	auto [x0, x1] = splat(x, 0, 1);
	EXPECT_EQ(x0, 1.0);
	EXPECT_EQ(x1, 2.0);
    }
    {
	auto [x1, x0] = splat(x, 1, 0);
	EXPECT_EQ(x0, 1.0);
	EXPECT_EQ(x1, 2.0);
    }
    {
	auto [x0, x1, x2] = splat(x, 0, 1, 2);
	EXPECT_EQ(x0, 1.0);
	EXPECT_EQ(x1, 2.0);
	EXPECT_EQ(x2, 3.0);
    }
    {
	auto [x2, x1, x0] = splat(x, 2, 1, 0);
	EXPECT_EQ(x0, 1.0);
	EXPECT_EQ(x1, 2.0);
	EXPECT_EQ(x2, 3.0);
    }
    EXPECT_THROW(splat(x, -1), core::runtime_error);
    EXPECT_THROW(splat(x, 3), core::runtime_error);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



