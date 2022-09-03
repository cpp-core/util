// Copyright 2018, 2019, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/signum.h"

TEST(SigNum, Negative)
{
    EXPECT_EQ(signum(-1), -1);
    EXPECT_EQ(signum(-1.0), -1);
}

TEST(SigNum, Positive)
{
    EXPECT_EQ(signum(1), 1);
    EXPECT_EQ(signum(1.0), 1);
}

TEST(SigNum, Zero)
{
    EXPECT_EQ(signum(0), 0);
    EXPECT_EQ(signum(0.0), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



