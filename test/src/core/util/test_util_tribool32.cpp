// Copyright 2019, 2021, 2022 by Mark Melton
//

#include <random>
#include <gtest/gtest.h>
#include "core/util/tribool32.h"

using namespace core::util;

void assert_is_unknown(tribool32 a) {
    EXPECT_EQ(a.is_true(), 0);
    EXPECT_EQ(a.is_false(), 0);
}

void assert_is_true(tribool32 a) {
    EXPECT_EQ(a.is_true(), 0xFFFFFFFF);
    EXPECT_EQ(a.is_false(), 0);
}

void assert_is_false(tribool32 a) {
    EXPECT_EQ(a.is_true(), 0);
    EXPECT_EQ(a.is_false(), 0xFFFFFFFF);
}

TEST(Tribool32, Initialization)
{
    tribool32 a{}, b{false}, c{true};
    for (auto i = 0; i < 32; ++i) {
	EXPECT_FALSE(a.is_known(i));
	EXPECT_TRUE(b.is_false(i));
	EXPECT_TRUE(c.is_true(i));
    }
}

TEST(Tribool32, Negation)
{
    auto rng = std::random_device();
    for (auto i = 0; i < 16; ++i) {
	auto n = rng(), m = rng() & ~n;
	tribool32 a{n, m}, b{m, n};
	EXPECT_EQ(~a, b);
    }

}

TEST(Tribool32, BinaryOps)
{
    auto rng = std::random_device();
    for (auto i = 0; i < 16; ++i) {
	auto n0 = rng(), m0 = rng() & ~n0;
	auto n1 = rng(), m1 = rng() & ~n1;
	tribool32 a{n0, m0}, b{n1, m1};
	EXPECT_EQ(a & b, tribool32(n0 & n1, m0 | m1));
	EXPECT_EQ(a | b, tribool32(n0 | n1, m0 & m1));
	EXPECT_EQ(a ^ b, tribool32((n0 & m1) | (n1 & m0), (n0 & n1) | (m0 & m1)));
	EXPECT_EQ(a + b, tribool32{});
	EXPECT_EQ(a - b, tribool32{});

	tribool32 x{n0}, y{m0};
	EXPECT_EQ(x + y, tribool32{n0 + m0});
	EXPECT_EQ(x - y, tribool32{n0 - m0});
    }
}

TEST(Tribool32, AnyAllNone)
{
    tribool32 a{0u, 55u}, b{1u, 54u}, c{~std::uint32_t{0}, 0u};
    EXPECT_FALSE(any(a));
    EXPECT_FALSE(all(a));
    EXPECT_TRUE(none(a));

    EXPECT_TRUE(any(b));
    EXPECT_FALSE(all(b));
    EXPECT_FALSE(none(b));

    EXPECT_TRUE(any(c));
    EXPECT_TRUE(all(c));
    EXPECT_FALSE(none(c));
}

TEST(Tribool32, IO)
{
    {
	tribool32 a;
	std::ostringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), std::string(32, '?'));
    }
    {
	tribool32 a{true};
	std::ostringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), std::string(32, '1'));
    }
    {
	tribool32 a{true};
	std::ostringstream ss;
	ss << std::boolalpha << a;
	EXPECT_EQ(ss.str(), std::string(32, 't'));
    }
    {
	tribool32 a{false};
	std::ostringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), std::string(32, '0'));
    }
    {
	tribool32 a{false};
	std::ostringstream ss;
	ss << std::boolalpha << a;
	EXPECT_EQ(ss.str(), std::string(32, 'f'));
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
