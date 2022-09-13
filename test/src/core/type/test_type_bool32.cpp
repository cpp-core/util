// Copyright 2019, 2021, 2022 by Mark Melton
//

#include <random>
#include <bit>
#include <gtest/gtest.h>
#include "core/type/bool32.h"

using namespace core::type;

TEST(Bool32, Initialization)
{
    bool32 a{}, b{false}, c{true};
    auto ax{a.as_uint()}, bx{b.as_uint()}, cx{c.as_uint()};
    EXPECT_EQ(ax, 0);
    EXPECT_EQ(bx, 0);
    EXPECT_EQ(cx, ~std::uint32_t{0});

    auto rng = std::random_device();
    for (auto i = 0; i < 16; ++i) {
	auto n = rng();
	bool32 d{n};
	EXPECT_EQ(d.as_uint(), n);
    }
}

TEST(Bool32, Access) {
    auto rng = std::random_device();
    for (auto i = 0; i < 16; ++i) {
	auto n = rng(), m = rng();
	bool32 a{n};
	for (auto j = 0; j < 32; ++j) {
	    auto elem = a[j];
	    EXPECT_EQ(elem, bool(n & (1u << j)));
	    a[j] = bool(m & (1u << j));
	}
	EXPECT_EQ(a.as_uint(), m);
    }
}

TEST(Bool32, Negation)
{
    auto rng = std::random_device();
    for (auto i = 0; i < 16; ++i) {
	auto n = rng();
	bool32 a{n};
	auto b = ~a;
	EXPECT_EQ(b.as_uint(), ~n);
    }
}

TEST(Bool32, BinaryOps)
{
    auto rng = std::random_device();
    for (auto i = 0; i < 16; ++i) {
	auto n = rng(), m = rng();
	bool32 a{n}, b{m};
	EXPECT_EQ(a & b, bool32{n & m});
	EXPECT_EQ(a | b, bool32{n | m});
	EXPECT_EQ(a ^ b, bool32{n ^ m});
	EXPECT_EQ(a + b, bool32{n + m});
	EXPECT_EQ(a - b, bool32{n - m});
    }
}

TEST(Bool32, RotationShift)
{
    auto rng = std::random_device();
    for (auto i = 0; i < 64; ++i) {
	auto n = rng(), m = rng() % 32;
	bool32 a{n};
	EXPECT_EQ(rotr(a, m).as_uint(), std::rotr(n, m));
	EXPECT_EQ(a >> m, bool32{n >> m});
    }
}

TEST(Bool32, AnyAllNone)
{
    bool32 a{0u}, b{1u}, c{~std::uint32_t{0}};
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

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
