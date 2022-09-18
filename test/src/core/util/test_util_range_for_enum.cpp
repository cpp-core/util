// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/range_for_enum.h"

using namespace core;

TEST(RangeForEnum, Enum)
{
    enum class E { a, b, c, Sentinel };
    std::vector<E> enums;
    for (auto e : RangeForEnum<E>{}) {
	enums.push_back(e);
    }
    ASSERT_EQ(enums.size(), 3);
    EXPECT_EQ(enums[0], E::a);
    EXPECT_EQ(enums[1], E::b);
    EXPECT_EQ(enums[2], E::c);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
