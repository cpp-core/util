// Copyright (C) 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/bit/sbs/sbs.h"
#include "core/range/sample.h"
#include "core/range/container.h"
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

template<template<class...> class C, class T>
void test_container() {
    auto g = cr::uniform<T>();
    auto n = cr::uniform<size_t>(0, 33);
    for (auto expected : cr::containerize<C<T>>(g, n) | v::take(NumberSamples)) {
	std::stringstream ss;
	to_sbs(ss, expected);

	C<T> actual;
	from_sbs(ss, actual);

	EXPECT_EQ(actual, expected);
    }
}

using BaseTypes = std::tuple<int16,int,int64,uint16,uint,uint64,float,real>;
using BriefBaseTypes = std::tuple<int,uint64,real>;
    
TEST(SBS, BaseTypes)
{
    core::mp::foreach<BaseTypes>([]<class T>() {
	    test_scalar<T>();
	});
}

TEST(SBS, Container)
{
    core::mp::foreach<BaseTypes>([]<class T>() {
	    test_container<std::vector,T>();
	    test_container<std::list,T>();
	});
}

TEST(SBS, Pair)
{
    core::mp::foreach<BriefBaseTypes>([]<class T>() {
	    core::mp::foreach<BriefBaseTypes>([]<class U>() {
		    auto gt = cr::uniform<T>();
		    auto gu = cr::uniform<U>();
		    auto gpair = v::zip(gt, gu) |
			v::transform([](auto r) { return std::make_pair(r.first, r.second); });
		    
		    for (auto expected : gpair | v::take(1)) {
			std::stringstream ss;
			to_sbs(ss, expected);

			std::pair<T,U> actual;
			from_sbs(ss, actual);
			
			EXPECT_EQ(actual, expected);
		    }
		});
	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
