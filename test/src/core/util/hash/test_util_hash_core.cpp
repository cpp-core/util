// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"
#include "core/util/hash/core.h"
#include "core/util/hash/detail/test_hash.h"

using Integral = std::tuple<std::int8_t,
			    std::int16_t,
			    std::int32_t,
			    std::int64_t,
			    std::uint8_t,
			    std::uint16_t,
			    std::uint32_t,
			    std::uint64_t>;

using Floating = std::tuple<float,
			    double>;

using Containers = std::tuple<std::vector<int>,
			      std::vector<double>,
			      std::vector<size_t>,
			      std::list<int>>;

TEST(Hash, String)
{
    test_hash<std::string>(1024);
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
