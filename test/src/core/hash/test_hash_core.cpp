// Copyright 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/hash/hash.h"
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"

using namespace costr;

template<class T>
void test_pod_generator() {
    map<T,size_t> counts;
    auto g = uniform<T>();
    for (auto elem : take(std::move(g), 1024)) {
	if (not counts.contains(elem))
	    counts[elem] = 0;
	++counts[elem];
	EXPECT_EQ(core::hash(elem), core::hash(elem));
    }
    for (const auto& [_, count] : counts)
	EXPECT_LE(count, 2);
}

template<class T>
void test_container_generator() {
    map<T,size_t> counts;
    auto g = uniform<T>();
    for (auto container : take(std::move(g), 32)) {
	if (container.size() == 0)
	    continue;
	if (not counts.contains(container))
	    counts[container] = 0;
	++counts[container];
	EXPECT_EQ(core::hash(container), core::hash(container));
    }
    for (const auto& [_, count] : counts)
	EXPECT_LE(count, 2);
}

using Pods = std::tuple<int16,int,int64,uint16,uint,uint64,float,double>;
using Containers = std::tuple<ints,reals,size_ts>;

TEST(Hash, Simple)
{
    core::mp::foreach<Pods>([]<class T>() {
    	    test_pod_generator<T>();
    	});
}

TEST(Hash, Container)
{
    core::mp::foreach<Containers>([]<class T>() {
	    test_container_generator<T>();
	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
