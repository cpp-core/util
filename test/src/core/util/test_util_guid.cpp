// Copyright 2019, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/guid.h"

TEST(GUID, Default)
{
    core::Guid g0, g1;
    EXPECT_TRUE(g0.nil());
    EXPECT_TRUE(g1.nil());
    EXPECT_EQ(g0, g1);
    
    auto str = g0.as_string();
    EXPECT_EQ(str, "00000000-0000-0000-0000-000000000000");
}

TEST(GUID, Generate)
{
    auto g0 = core::Guid::generate();
    auto g1 = core::Guid::generate();

    EXPECT_FALSE(g0.nil());
    EXPECT_FALSE(g1.nil());
    EXPECT_NE(g0, g1);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
