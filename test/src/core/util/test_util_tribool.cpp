// Copyright 2019, 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/tribool.h"

using namespace core::util;

void assert_is_unknown(tribool a) {
    EXPECT_FALSE(a.is_known());
    EXPECT_FALSE(a.is_true());
    EXPECT_FALSE(a.is_false());
}

void assert_is_true(tribool a) {
    EXPECT_TRUE(a.is_known());
    EXPECT_TRUE(a.is_true());
    EXPECT_FALSE(a.is_false());
}

void assert_is_false(tribool a) {
    EXPECT_TRUE(a.is_known());
    EXPECT_FALSE(a.is_true());
    EXPECT_TRUE(a.is_false());
}

TEST(Tribool, Initialization)
{
    tribool a{}, b{false}, c{true}, d{std::nullopt};
    assert_is_unknown(a);
    assert_is_false(b);
    assert_is_true(c);
    assert_is_unknown(d);
}

TEST(Tribool, Assign)
{
    tribool a;
    a = std::nullopt;
    assert_is_unknown(a);
    
    a = tribool{false};
    assert_is_false(a);

    a = tribool{true};
    assert_is_true(a);
}

TEST(Tribool, ChoiceA)
{
    {
	tribool a, b{false}, c{true};
	auto ar = a << tribool{}, br = b << tribool{}, cr = c << tribool{};
	assert_is_unknown(ar);
	assert_is_false(br);
	assert_is_true(cr);
    }
    {
	tribool a, b{false}, c{true};
	auto ar = a << tribool{false}, br = b << tribool{false}, cr = c << tribool{false};
	assert_is_false(ar);
	assert_is_false(br);
	assert_is_true(cr);
    }
    {
	tribool a, b{false}, c{true};
	auto ar = a << tribool{true}, br = b << tribool{true}, cr = c << tribool{true};
	assert_is_true(ar);
	assert_is_false(br);
	assert_is_true(cr);
    }
}

TEST(Tribool, ChoiceAEquals)
{
    {
	tribool a, b{false}, c{true};
	a << tribool{}, b << tribool{}, c << tribool{};
	assert_is_unknown(a);
	assert_is_false(b);
	assert_is_true(c);
    }
    {
	tribool a, b{false}, c{true};
	a << tribool{false}, b << tribool{false}, c << tribool{false};
	assert_is_false(a);
	assert_is_false(b);
	assert_is_true(c);
    }
    {
	tribool a, b{false}, c{true};
	a << tribool{true}, b << tribool{true}, c << tribool{true};
	assert_is_true(a);
	assert_is_false(b);
	assert_is_true(c);
    }
}

TEST(Tribool, ChoiceB)
{
    {
	tribool a, b{false}, c{true};
	auto ar = a <<= tribool{}, br = b <<= tribool{}, cr = c <<= tribool{};
	assert_is_unknown(ar);
	assert_is_false(br);
	assert_is_true(cr);
    }
    {
	tribool a, b{false}, c{true};
	auto ar = a <<= tribool{false}, br = b <<= tribool{false}, cr = c <<= tribool{false};
	assert_is_false(ar);
	assert_is_false(br);
	assert_is_false(cr);
    }
    {
	tribool a, b{false}, c{true};
	auto ar = a <<= tribool{true}, br = b <<= tribool{true}, cr = c <<= tribool{true};
	assert_is_true(ar);
	assert_is_true(br);
	assert_is_true(cr);
    }
}

TEST(Tribool, ChoiceBEquals)
{
    {
	tribool a, b{false}, c{true};
	a <<= tribool{}, b <<= tribool{}, c <<= tribool{};
	assert_is_unknown(a);
	assert_is_false(b);
	assert_is_true(c);
    }
    {
	tribool a, b{false}, c{true};
	a <<= tribool{false}, b <<= tribool{false}, c <<= tribool{false};
	assert_is_false(a);
	assert_is_false(b);
	assert_is_false(c);
    }
    {
	tribool a, b{false}, c{true};
	a <<= tribool{true}, b <<= tribool{true}, c <<= tribool{true};
	assert_is_true(a);
	assert_is_true(b);
	assert_is_true(c);
    }
}

TEST(Tribool, ForceUpdate)
{
    {
	tribool a, b{false}, c{true};
	a <<= tribool{}, b <<= tribool{}, c <<= tribool{};
	assert_is_unknown(a);
	assert_is_false(b);
	assert_is_true(c);
    }
    {
	tribool a, b{false}, c{true};
	a <<= tribool{false}, b <<= tribool{false}, c <<= tribool{false};
	assert_is_false(a);
	assert_is_false(b);
	assert_is_false(c);
    }
    {
	tribool a, b{false}, c{true};
	a <<= tribool{true}, b <<= tribool{true}, c <<= tribool{true};
	assert_is_true(a);
	assert_is_true(b);
	assert_is_true(c);
    }
}

TEST(Tribool, Equality)
{
    EXPECT_TRUE(tribool{} == tribool{});
    EXPECT_FALSE(tribool{} == tribool{false});
    EXPECT_FALSE(tribool{} == tribool{true});

    EXPECT_FALSE(tribool{false} == tribool{});
    EXPECT_TRUE(tribool{false} == tribool{false});
    EXPECT_FALSE(tribool{false} == tribool{true});

    EXPECT_FALSE(tribool{true} == tribool{});
    EXPECT_FALSE(tribool{true} == tribool{false});
    EXPECT_TRUE(tribool{true} == tribool{true});
}

TEST(Tribool, Negation)
{
    assert_is_unknown(~tribool{});
    assert_is_true(~tribool{false});
    assert_is_false(~tribool{true});
}

TEST(Tribool, Conjunction)
{
    assert_is_unknown(tribool{} & tribool{});
    assert_is_false(tribool{} & tribool{false});
    assert_is_unknown(tribool{} & tribool{true});

    assert_is_false(tribool{false} & tribool{});
    assert_is_false(tribool{false} & tribool{false});
    assert_is_false(tribool{false} & tribool{true});

    assert_is_unknown(tribool{true} & tribool{});
    assert_is_false(tribool{true} & tribool{false});
    assert_is_true(tribool{true} & tribool{true});
}

TEST(Tribool, Disjunction)
{
    assert_is_unknown(tribool{} | tribool{});
    assert_is_unknown(tribool{} | tribool{false});
    assert_is_true(tribool{} | tribool{true});

    assert_is_unknown(tribool{false} | tribool{});
    assert_is_false(tribool{false} | tribool{false});
    assert_is_true(tribool{false} | tribool{true});

    assert_is_true(tribool{true} | tribool{});
    assert_is_true(tribool{true} | tribool{false});
    assert_is_true(tribool{true} | tribool{true});
}

TEST(Tribool, ExclusiveDisjunction)
{
    assert_is_unknown(tribool{} ^ tribool{});
    assert_is_unknown(tribool{} ^ tribool{false});
    assert_is_unknown(tribool{} ^ tribool{true});

    assert_is_unknown(tribool{false} ^ tribool{});
    assert_is_false(tribool{false} ^ tribool{false});
    assert_is_true(tribool{false} ^ tribool{true});

    assert_is_unknown(tribool{true} ^ tribool{});
    assert_is_true(tribool{true} ^ tribool{false});
    assert_is_false(tribool{true} ^ tribool{true});
}

TEST(Tribool, AnyAllNone)
{
    tribool a, b{false}, c{true};
    EXPECT_FALSE(any(a));
    EXPECT_FALSE(all(a));
    EXPECT_TRUE(none(a));

    EXPECT_FALSE(any(b));
    EXPECT_FALSE(all(b));
    EXPECT_TRUE(none(b));

    EXPECT_TRUE(any(c));
    EXPECT_TRUE(all(c));
    EXPECT_FALSE(none(c));
}

TEST(Tribool, IO)
{
    {
	tribool a;
	std::ostringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), "?");
    }
    {
	tribool a{true};
	std::ostringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), "1");
    }
    {
	tribool a{true};
	std::ostringstream ss;
	ss << std::boolalpha << a;
	EXPECT_EQ(ss.str(), "t");
    }
    {
	tribool a{false};
	std::ostringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), "0");
    }
    {
	tribool a{false};
	std::ostringstream ss;
	ss << std::boolalpha << a;
	EXPECT_EQ(ss.str(), "f");
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
