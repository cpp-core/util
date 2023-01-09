// Copyright (C) 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/view.h"

TEST(View, C0)
{
    auto s = std::span<const char>{};
    EXPECT_EQ(s.data(), nullptr);
    EXPECT_EQ(s.size(), std::span<char>::size_type{0});
}

TEST(View, C1)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    auto r = s;
    EXPECT_EQ(r.data(), buffer);
    EXPECT_EQ(r.size(), strlen(buffer));
    EXPECT_EQ(std::string(r.begin(), r.end()), "abcdef");
}

TEST(View, C2)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.data(), buffer);
    EXPECT_EQ(s.size(), strlen(buffer));
    EXPECT_EQ(std::string(s.begin(), s.end()), "abcdef");
}

TEST(View, C3)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, buffer + strlen(buffer)};
    EXPECT_EQ(s.data(), buffer);
    EXPECT_EQ(s.size(), strlen(buffer));
    EXPECT_EQ(std::string(s.begin(), s.end()), "abcdef");
}

TEST(View, C4)
{
    const std::string buffer = "abcdef";
    auto s = std::span{buffer.c_str(), buffer.size()};
    EXPECT_EQ(s.data(), buffer);
    EXPECT_EQ(s.size(), buffer.size());
    EXPECT_EQ(std::string(s.begin(), s.end()), "abcdef");
}

TEST(View, ArrayOperator)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    for (size_t i = 0; i < (size_t)strlen(buffer); ++i)
	EXPECT_EQ(s[i], buffer[i]);
}

TEST(View, At)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    for (size_t i = 0; i < (size_t)strlen(buffer); ++i)
	EXPECT_EQ(at(s, i), buffer[i]);
}

TEST(View, Front)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.front(), buffer[0]);
}

TEST(View, Back)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.back(), buffer[strlen(buffer) - 1]);
}

TEST(View, Data)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.data(), &buffer[0]);
}

TEST(View, Size)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.size(), strlen(buffer));
}

TEST(View, EmptyTrue)
{
    auto s = std::span<char>{};
    EXPECT_EQ(s.empty(), true);
}

TEST(View, EmptyFalse)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.empty(), false);
}

TEST(View, First)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    auto r = s.first(3);
    EXPECT_EQ(r.data(), s.data());
    EXPECT_EQ(r.size(), 3);
    EXPECT_EQ(std::string(r.begin(), r.end()), "abc");
}

TEST(View, Last)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    auto r = s.last(3);
    EXPECT_EQ(r.data(), s.data() + 3);
    EXPECT_EQ(r.size(), 3);
    EXPECT_EQ(std::string(r.begin(), r.end()), "def");
}

TEST(View, Subspan)
{
    const char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    auto r = s.subspan(1, 4);
    EXPECT_EQ(r.data(), s.data() + 1);
    EXPECT_EQ(r.size(), 4);
    EXPECT_EQ(std::string(r.begin(), r.end()), "bcde");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
