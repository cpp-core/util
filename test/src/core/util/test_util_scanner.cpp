// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/scanner.h"

using namespace core::util;

TEST(Scanner, MaybeMatch)
{
    auto str = "abc,def";
    Scanner scanner{str};
    auto result = scanner.maybe_consume_to(',');
    EXPECT_EQ(result, "abc");
}

TEST(Scanner, Match)
{
    auto str = "abc,def";
    Scanner scanner{str};
    auto result = scanner.consume_to(',');
    EXPECT_EQ(result, "abc");
}

TEST(Scanner, MaybeEnd)
{
    auto str = "abc";
    Scanner scanner{str};
    auto result = scanner.maybe_consume_to(',');
    EXPECT_EQ(result, "abc");
}

TEST(Scanner, End)
{
    auto str = "abc";
    Scanner scanner{str};
    auto result = scanner.consume_to(',');
    EXPECT_EQ(result, "abc");
}

TEST(Scanner, MaybeEmpty)
{
    auto str = "abc,";
    Scanner scanner{str};
    scanner.maybe_consume_to(',');
    auto result = scanner.maybe_consume_to(',');
    EXPECT_EQ(result, "");
}

TEST(Scanner, Empty)
{
    auto str = "abc,";
    Scanner scanner{str};
    scanner.consume_to(',');
    EXPECT_THROW(scanner.consume_to(','), std::runtime_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



