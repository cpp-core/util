// Copyright (C) 2019, 2021, 2022, 2023 by Mark Melton
//

#include <span>
#include <gtest/gtest.h>
#include "core/util/span.h"

TEST(Span, C0)
{
    auto s = std::span<char>{};
    EXPECT_EQ(s.data(), nullptr);
    EXPECT_EQ(s.size(), std::span<char>::size_type{0});
}

TEST(Span, C1)
{
    char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    auto r = s;
    EXPECT_EQ(r.data(), buffer);
    EXPECT_EQ(r.size(), strlen(buffer));
    EXPECT_EQ(std::string(r.begin(), r.end()), "abcdef");
}

TEST(Span, C2)
{
    char buffer[] = "abcdef";
    auto s = std::span{buffer, strlen(buffer)};
    EXPECT_EQ(s.data(), buffer);
    EXPECT_EQ(s.size(), strlen(buffer));
    EXPECT_EQ(std::string(s.begin(), s.end()), "abcdef");
}

TEST(Span, C3)
{
    char buffer[] = "abcdef";
    auto s = std::span{buffer, buffer + strlen(buffer)};
    EXPECT_EQ(s.data(), buffer);
    EXPECT_EQ(s.size(), strlen(buffer));
    EXPECT_EQ(std::string(s.begin(), s.end()), "abcdef");
}

TEST(Span, C4)
{
    std::string buffer = "abcdef";
    auto s = std::span{buffer.c_str(), buffer.size()};
    EXPECT_EQ(s.data(), buffer);
    EXPECT_EQ(s.size(), buffer.size());
    EXPECT_EQ(std::string(s.begin(), s.end()), "abcdef");
}

TEST(Span, ArrayOperator)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    for (auto i = 0; i < strlen(buffer); ++i)
	EXPECT_EQ(s[i], buffer[i]);
    
    s[2] = 'x';
    EXPECT_EQ(buffer[2], 'x');
}

TEST(Span, At)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    for (auto i = 0; i < strlen(buffer); ++i)
     	EXPECT_EQ((at<char>(s, i)), buffer[i]);

    at(s, 2) = 'x';
    EXPECT_EQ(buffer[2], 'x');
}

TEST(Span, Front)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    EXPECT_EQ(s.front(), buffer[0]);
    
    s.front() = 'x';
    EXPECT_EQ(buffer[0], 'x');
}

TEST(Span, Back)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    EXPECT_EQ(s.back(), buffer[strlen(buffer) - 1]);
    
    s.back() = 'x';
    EXPECT_EQ(buffer[strlen(buffer) - 1], 'x');
}

TEST(Span, Data)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    EXPECT_EQ(s.data(), &buffer[0]);
}

TEST(Span, Size)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    EXPECT_EQ(s.size(), strlen(buffer));
}

TEST(Span, EmptyTrue)
{
    auto s = std::span<char>{};
    EXPECT_EQ(s.empty(), true);
}

TEST(Span, EmptyFalse)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    EXPECT_EQ(s.empty(), false);
}

TEST(Span, First)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = s.first(3);
    EXPECT_EQ(r.data(), s.data());
    EXPECT_EQ(r.size(), 3);
    EXPECT_EQ(std::string(r.begin(), r.end()), "abc");
}

TEST(Span, Last)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = s.last(3);
    EXPECT_EQ(r.data(), s.data() + 3);
    EXPECT_EQ(r.size(), 3);
    EXPECT_EQ(std::string(r.begin(), r.end()), "def");
}

TEST(Span, Subspan)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = s.subspan(1, 4);
    EXPECT_EQ(r.data(), s.data() + 1);
    EXPECT_EQ(r.size(), 4);
    EXPECT_EQ(std::string(r.begin(), r.end()), "bcde");
}

TEST(Span, ShiftRight)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = shift(s, 1);
    EXPECT_EQ(r.data(), s.data() + 1);
    EXPECT_EQ(r.size(), s.size() - 1);
    EXPECT_EQ(std::string(r.begin(), r.end()), "bcdef");
}

TEST(Span, ShiftLeft)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = shift(s, -1);
    EXPECT_EQ(r.data(), s.data());
    EXPECT_EQ(r.size(), s.size() - 1);
    EXPECT_EQ(std::string(r.begin(), r.end()), "abcde");
}

TEST(Span, TrimRight)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = rtrim(s, 1);
    EXPECT_EQ(r.data(), s.data());
    EXPECT_EQ(r.size(), s.size() - 1);
    EXPECT_EQ(std::string(r.begin(), r.end()), "abcde");
}

TEST(Span, TrimLeft)
{
    char buffer[] = "abcdef";
    auto s = std::span<char>{buffer, strlen(buffer)};
    auto r = ltrim(s, 1);
    EXPECT_EQ(r.data(), s.data() + 1);
    EXPECT_EQ(r.size(), s.size() - 1);
    EXPECT_EQ(std::string(r.begin(), r.end()), "bcdef");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
