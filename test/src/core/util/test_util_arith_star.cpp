// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util//arith_star.h"

TEST(ArithStar, Min)
{
    EXPECT_EQ(min_star(1), 1);
    EXPECT_EQ(min_star(1,2), 1);
    EXPECT_EQ(min_star(1,2,3), 1);
    EXPECT_EQ(min_star(1,2,3,4), 1);

    EXPECT_EQ(min_star(1,2ll,3ul,4u), 1);
}

TEST(ArithStar, Max)
{
    EXPECT_EQ(max_star(1), 1);
    EXPECT_EQ(max_star(1,2), 2);
    EXPECT_EQ(max_star(1,2,3), 3);
    EXPECT_EQ(max_star(1,2,3,4), 4);

    EXPECT_EQ(max_star(1,2ll,3ul,4u), 4);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



