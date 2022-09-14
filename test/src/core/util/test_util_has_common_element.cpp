// Copyright 2018, 2019, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/has_common_element.h"

TEST(HasCommonElement, Empty)
{
    std::vector<int> a, b = { 1, 2, 3 };
    EXPECT_FALSE(has_common_element(a, b));
    EXPECT_FALSE(has_common_element(b, a));
}

TEST(HasCommonElement, Same)
{
    std::vector<int> a = { 1, 2, 3 }, b = { 1, 2, 3 };
    EXPECT_TRUE(has_common_element(a, b));
    EXPECT_TRUE(has_common_element(b, a));
}

TEST(HasCommonElement, Intersecting)
{
    std::vector<int> a = { 1, 2, 3 }, b = { 2, 4, 6 };
    EXPECT_TRUE(has_common_element(a, b));
    EXPECT_TRUE(has_common_element(b, a));
}

TEST(HasCommonElement, NonIntersecting)
{
    std::vector<int> a = { 1, 3, 5 }, b = { 2, 4, 6 };
    EXPECT_FALSE(has_common_element(a, b));
    EXPECT_FALSE(has_common_element(b, a));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



