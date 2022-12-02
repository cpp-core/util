// Copyright 2019, 2022 by Mark Melton
//

#include <vector>
#include <gtest/gtest.h>
#include "core/util/for_while.h"

using namespace core;

TEST(Util, ForWhile)
{
    size_t sum{0};
    std::vector<int> a = { 0, 1, 2, 3, 4, 5 };
    int idx = for_while(a, [](int n) { return n < 3; }, [&](int n) { sum += n; });
    EXPECT_EQ(idx, 3);
    EXPECT_EQ(sum, 3);
}

TEST(Util, ReverseForWhile)
{
    size_t sum{0};
    std::vector<int> a = { 0, 1, 2, 3, 4, 5 };
    int idx = rfor_while(a, [](int n) { return n > 2; }, [&](int n) { sum += n; });
    EXPECT_EQ(idx, 2);
    EXPECT_EQ(sum, 12);
}

TEST(Util, ForIndexWhile)
{
    size_t sum{0};
    std::vector<int> a = { 0, 1, 2, 3, 4, 5 };
    auto idx = for_index_while(a, [&](int i) { return a[i] < 3; }, [&](int i) { sum += a[i]; });
    EXPECT_EQ(idx, 3);
    EXPECT_EQ(sum, 3);
}

TEST(Util, ReverseForIndexWhile)
{
    size_t sum{0};
    std::vector<int> a = { 0, 1, 2, 3, 4, 5 };
    auto idx = rfor_index_while(a, [&](int i) { return a[i] > 2; }, [&](int i) { sum += a[i]; });
    EXPECT_EQ(idx, 2);
    EXPECT_EQ(sum, 12);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
