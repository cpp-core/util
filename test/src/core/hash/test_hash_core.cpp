// Copyright 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"
#include "core/hash/core.h"
#include "core/hash/detail/test_hash.h"

using Integral = std::tuple<int8,int16,int32,int64,uint8,uint16,uint32,uint64>;
using Floating = std::tuple<real32,real64>;
using Containers = std::tuple<ints,reals,size_ts,std::list<int>>;

TEST(Hash, String)
{
    test_hash<string>(1024);
}

TEST(Hash, Integral)
{
    core::mp::foreach<Integral>([]<class T>() {
    	    test_hash<T>(1024);
    	});
}

TEST(Hash, Floating)
{
    core::mp::foreach<Floating>([]<class T>() {
    	    test_hash<T>(1024);
    	});
}

TEST(Hash, Container)
{
    core::mp::foreach<Containers>([]<class T>() {
    	    test_hash<T>(16);
    	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
