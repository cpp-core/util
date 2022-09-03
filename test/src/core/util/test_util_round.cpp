// Copyright 2018, 2019, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/round.h"

TEST(Round, Floor)
{
    EXPECT_DOUBLE_EQ(floor(100.004, 0.05, 0.0), 100.00);
    EXPECT_DOUBLE_EQ(floor(100.014, 0.05, 0.0), 100.00);
    EXPECT_DOUBLE_EQ(floor(100.024, 0.05, 0.0), 100.00);
    EXPECT_DOUBLE_EQ(floor(100.034, 0.05, 0.0), 100.00);
    EXPECT_DOUBLE_EQ(floor(100.044, 0.05, 0.0), 100.00);
    EXPECT_DOUBLE_EQ(floor(100.054, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(floor(100.064, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(floor(100.074, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(floor(100.084, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(floor(100.094, 0.05, 0.0), 100.05);

    EXPECT_DOUBLE_EQ(floor(100.004, 0.05, 0.01),  99.96);
    EXPECT_DOUBLE_EQ(floor(100.014, 0.05, 0.01), 100.01);
    EXPECT_DOUBLE_EQ(floor(100.024, 0.05, 0.01), 100.01);
    EXPECT_DOUBLE_EQ(floor(100.034, 0.05, 0.01), 100.01);
    EXPECT_DOUBLE_EQ(floor(100.044, 0.05, 0.01), 100.01);
    EXPECT_DOUBLE_EQ(floor(100.054, 0.05, 0.01), 100.01);
    EXPECT_DOUBLE_EQ(floor(100.064, 0.05, 0.01), 100.06);
    EXPECT_DOUBLE_EQ(floor(100.074, 0.05, 0.01), 100.06);
    EXPECT_DOUBLE_EQ(floor(100.084, 0.05, 0.01), 100.06);
    EXPECT_DOUBLE_EQ(floor(100.094, 0.05, 0.01), 100.06);
}

TEST(Round, Ceil)
{
    EXPECT_DOUBLE_EQ(ceil(100.004, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(ceil(100.014, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(ceil(100.024, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(ceil(100.034, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(ceil(100.044, 0.05, 0.0), 100.05);
    EXPECT_DOUBLE_EQ(ceil(100.054, 0.05, 0.0), 100.10);
    EXPECT_DOUBLE_EQ(ceil(100.064, 0.05, 0.0), 100.10);
    EXPECT_DOUBLE_EQ(ceil(100.074, 0.05, 0.0), 100.10);
    EXPECT_DOUBLE_EQ(ceil(100.084, 0.05, 0.0), 100.10);
    EXPECT_DOUBLE_EQ(ceil(100.094, 0.05, 0.0), 100.10);

    EXPECT_DOUBLE_EQ(ceil(100.004, 0.05, 0.01), 100.04);
    EXPECT_DOUBLE_EQ(ceil(100.014, 0.05, 0.01), 100.04);
    EXPECT_DOUBLE_EQ(ceil(100.024, 0.05, 0.01), 100.04);
    EXPECT_DOUBLE_EQ(ceil(100.034, 0.05, 0.01), 100.04);
    EXPECT_DOUBLE_EQ(ceil(100.044, 0.05, 0.01), 100.09);
    EXPECT_DOUBLE_EQ(ceil(100.054, 0.05, 0.01), 100.09);
    EXPECT_DOUBLE_EQ(ceil(100.064, 0.05, 0.01), 100.09);
    EXPECT_DOUBLE_EQ(ceil(100.074, 0.05, 0.01), 100.09);
    EXPECT_DOUBLE_EQ(ceil(100.084, 0.05, 0.01), 100.09);
    EXPECT_DOUBLE_EQ(ceil(100.094, 0.05, 0.01), 100.14);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



