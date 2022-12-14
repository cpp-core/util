// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/range_for_zip.h"

using namespace core;
using namespace std::string_literals;

TEST(RangeForZip, Smoke)
{
    auto a = "abc"s;
    auto b = "def"s;

    auto r = ""s;
    auto s = ""s;

    for (auto [first, second] : RangeForZip{a, b}) {
	r += first;
	s += second;
    }

    EXPECT_EQ(a, r);
    EXPECT_EQ(b, s);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
