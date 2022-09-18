// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/range_for_pair.h"

using namespace core;

TEST(RangeForPair, Types)
{
    int *b{nullptr}, *e{nullptr};
    std::pair<int*,int*> pair{b, e};
    
    auto rfp = core::RangeForPair{b, e};
    using T = decltype(rfp);
    EXPECT_TRUE((std::is_same_v<typename T::Pair, std::pair<int*,int*>>));

    auto rfp_ref = core::RangeForPair{pair};
    using TREF = decltype(rfp_ref);
    EXPECT_TRUE((std::is_same_v<typename TREF::Pair, std::pair<int*,int*>&>));
    
    auto rfp_copy = core::RangeForPair{std::pair{b, e}};
    using TCOPY = decltype(rfp_copy);
    EXPECT_TRUE((std::is_same_v<typename TCOPY::Pair, std::pair<int*,int*>>));
}

TEST(RangeForPair, VectorInt)
{
    std::vector<int> data{1, 2, 3};
    
    std::vector<int> actual;
    for (auto elem : core::RangeForPair{data.begin(), data.end()})
	actual.push_back(elem);
    EXPECT_EQ(actual, data);

    std::vector<int> actual_pair_ref;
    auto pair = std::make_pair(data.begin(), data.end());
    for (auto elem : core::RangeForPair{pair})
	actual_pair_ref.push_back(elem);
    EXPECT_EQ(actual_pair_ref, data);
    
    std::vector<int> actual_pair_copy;
    for (auto elem : core::RangeForPair{std::make_pair(data.begin(), data.end())})
	actual_pair_copy.push_back(elem);
    EXPECT_EQ(actual_pair_copy, data);
}

TEST(RangeForPair, VectorString)
{
    std::vector<std::string> data{"abc", "def", "ghi"};

    std::vector<std::string> actual;
    for (auto elem : core::RangeForPair{data.begin(), data.end()})
	actual.push_back(elem);
    EXPECT_EQ(actual, data);

    std::vector<std::string> actual_pair_ref;
    auto pair = std::make_pair(data.begin(), data.end());
    for (auto elem : core::RangeForPair{pair})
	actual_pair_ref.push_back(elem);
    EXPECT_EQ(actual_pair_ref, data);
    
    std::vector<std::string> actual_pair_copy;
    for (auto elem : core::RangeForPair{std::make_pair(data.begin(), data.end())})
	actual_pair_copy.push_back(elem);
    EXPECT_EQ(actual_pair_copy, data);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
