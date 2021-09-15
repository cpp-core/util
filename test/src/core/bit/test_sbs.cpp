// Copyright (C) 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/bit/sbs.h"
#include "core/range/sample.h"
#include "core/mp/foreach.h"

using namespace core;

const size_t NumberSamples = 64;

template<class T>
void test_scalar() {
    auto g = cr::uniform<T>();
    for (auto expected : g | v::take(NumberSamples)) {
	std::stringstream ss;
	to_sbs(ss, expected);

	T actual;
	from_sbs(ss, actual);

	EXPECT_EQ(actual, expected);
    }
}

template<class T>
void test_container() {
    auto g = cr::uniform<T>();
}

using BasicTypes = std::tuple<int,int64,uint,uint64,float,real>;

TEST(SBS, BasicTypes)
{
    core::mp::foreach<BasicTypes>([]<class T>() {
	    test_scalar<T>();
	});
}

TEST(SBS, Containers)
{
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
