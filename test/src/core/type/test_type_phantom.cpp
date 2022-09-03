// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/type/phantom.h"

using namespace core::type;

TEST(Phantom, String)
{
    struct Name : public Phantom<std::string> {};
    
    std::stringstream ss;
    Name foo{"abc"s};
    ss << foo;
    EXPECT_EQ(ss.str(), "abc");

    json j = foo;
    auto bar = j.get<Name>();
    EXPECT_EQ(foo.value(), bar.value());
}

TEST(Phantom, Int)
{
    struct Value : public Phantom<int> {};
    
    std::stringstream ss;
    Value foo{42};
    ss << foo;
    EXPECT_EQ(ss.str(), "42");

    json j = foo;
    auto bar = j.get<Value>();
    EXPECT_EQ(foo.value(), bar.value());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
