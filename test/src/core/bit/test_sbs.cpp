// Copyright (C) 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/bit/sbs/sbs.h"
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"

using namespace core;
using namespace costr;

const size_t NumberSamples = 64;

template<class T>
void test_with_generator() {
    auto g = uniform<T>();
    for (auto elem : take(std::move(g), NumberSamples)) {
	std::stringstream ss;
	to_sbs(ss, elem);

	T actual;
	from_sbs(ss, actual);
	EXPECT_EQ(actual, elem);
    }
}

using BaseTypes = std::tuple<int16,int,int64,uint16,uint,uint64,float,real,string>;
using BriefBaseTypes = std::tuple<int,std::vector<real>,string>;
    
TEST(SBS, BaseTypes)
{
    core::mp::foreach<BaseTypes>([]<class T>() {
	    test_with_generator<T>();
	});
}

TEST(SBS, Pair)
{
    core::mp::foreach<BriefBaseTypes>([]<class T>() {
	    core::mp::foreach<BriefBaseTypes>([]<class U>() {
		    test_with_generator<std::pair<T,U>>();
		});
	});
}

TEST(SBS, Container)
{
    core::mp::foreach<BriefBaseTypes>([]<class T>() {
	    test_with_generator<std::vector<T>>();
	    test_with_generator<std::list<T>>();
	    test_with_generator<std::deque<T>>();
	    test_with_generator<std::set<T>>();
	});
}

TEST(SBS, ContainerContainer)
{
    core::mp::foreach<BriefBaseTypes>([]<class T>() {
	    test_with_generator<std::vector<std::vector<T>>>();
	    test_with_generator<std::vector<std::list<T>>>();
	    test_with_generator<std::vector<std::deque<T>>>();
	    test_with_generator<std::vector<std::set<T>>>();
	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
