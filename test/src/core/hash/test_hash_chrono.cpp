// Copyright 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/hash/hash_chrono.h"
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"
#include "coro/stream/uniform_chrono.h"
#include "core/hash/test_hash.h"

constexpr size_t NumberSamples = 1024;

using namespace chron;

TEST(Hash, Date)
{
    test_hash<Date>(NumberSamples);
}

TEST(Hash, TimePoint)
{
    core::mp::foreach<TimePointAll>([]<class T>() {
	    test_hash<T>(NumberSamples);
	});
}

TEST(Hash, Duration)
{
    core::mp::foreach<DurationAll>([]<class T>() {
	    test_hash<T>(NumberSamples);
	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
