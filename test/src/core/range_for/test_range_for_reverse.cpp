// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/range_for/range_for_reverse.h"
#include "coro/stream/stream.h"

using namespace core;
using namespace coro;

static const int NumberSamples = 16;

TEST(RangeForReverse, Basic)
{
    for (auto vec : sampler<std::vector<int>>() | take(NumberSamples)) {
	std::vector<int> actual;
	for (auto& elem : RangeForReverse(vec))
	    actual.push_back(elem);
	std::vector<int> expected{vec.rbegin(), vec.rend()};
	EXPECT_EQ(actual, expected);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
