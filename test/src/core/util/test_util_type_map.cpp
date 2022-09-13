// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/type_map.h"

using core::TypeMap;
using namespace std::string_literals;

TEST(TypeMap, Construct)
{
    TypeMap map;
    EXPECT_EQ(map.size(), 0);

    TypeMap map1{1};
    EXPECT_EQ(map1.size(), 1);

    TypeMap map2{1, 2u};
    EXPECT_EQ(map2.size(), 2);

    EXPECT_THROW((TypeMap{1, 2}), std::runtime_error);
}

TEST(TypeMap, Insert)
{
    TypeMap map;

    map.insert(1);
    EXPECT_EQ(map.size(), 1);

    EXPECT_THROW(map.insert(1), std::runtime_error);

    map.insert(2u, 3.0);
    EXPECT_EQ(map.size(), 3);
}

TEST(TypeMap, Upsert)
{
    TypeMap map;

    map.upsert(1);
    EXPECT_EQ(map.size(), 1);

    map.upsert(2);
    EXPECT_EQ(map.size(), 1);

    map.upsert(2u, 3.0);
    EXPECT_EQ(map.size(), 3);
}

TEST(TypeMap, Remove)
{
    TypeMap map{1, 2u, 3.0};
    EXPECT_EQ(map.size(), 3);

    map.remove<int>();
    EXPECT_EQ(map.size(), 2);
    
    map.remove(2u);
    EXPECT_EQ(map.size(), 1);

    map.remove("abc"s);
    EXPECT_EQ(map.size(), 1);
}

TEST(TypeMap, Clear)
{
    TypeMap map{1, 2u, 3.0};
    EXPECT_EQ(map.size(), 3);

    map.clear();
    EXPECT_EQ(map.size(), 0);
}

TEST(TypeMap, Contains)
{
    TypeMap map{1, 2u, 3.0};

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(2u));
    EXPECT_TRUE(map.contains(3.0));

    EXPECT_FALSE(map.contains(2));
    EXPECT_FALSE(map.contains(3u));
    EXPECT_FALSE(map.contains(4.0));
    
    EXPECT_TRUE(map.contains<int>());
    EXPECT_TRUE(map.contains<uint>());
    EXPECT_TRUE(map.contains<double>());

    EXPECT_FALSE(map.contains<std::string>());
}

TEST(TypeMap, Get)
{
    TypeMap map{1, 2u, 3.0};

    EXPECT_EQ(map.get<int>(), 1);
    EXPECT_EQ(map.get<uint>(), 2u);
    EXPECT_EQ(map.get<double>(), 3.0);
    EXPECT_THROW(map.get<std::string>(), std::runtime_error);

    auto& value = map.get<int>();
    EXPECT_EQ(value, 1);
    value = 42;
    EXPECT_EQ(map.get<int>(), 42);
}

TEST(TypeMap, GetOrElse)
{
    TypeMap map{1, 2u, 3.0};
    
    EXPECT_EQ(map.get_or_else(2), 1);
    EXPECT_EQ(map.get_or_else(3u), 2);
    EXPECT_EQ(map.get_or_else(4.0), 3.0);
    EXPECT_EQ(map.get_or_else("abc"s), "abc"s);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
