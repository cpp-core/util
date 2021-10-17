// Copyright 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/hash/hash_chrono.h"
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"
#include "coro/stream/uniform_chrono.h"

using namespace chron;
using namespace costr;

constexpr size_t NumberSamples = 1024;

template<class T>
void test_hash() {
    set<uint64> hashes;
    set<T> tps;
    auto tpG = Uniform<T>{}();
    for (auto tp : take(std::move(tpG), NumberSamples)) {
	auto hid = core::hash(tp);
	auto hid_same = core::hash(tp);
	EXPECT_EQ(hid, hid_same);

	if (not tps.contains(tp))
	    EXPECT_FALSE(hashes.contains(hid));
	
	tps.insert(tp);
	hashes.insert(hid);
    }
}

TEST(Hash, Date)
{
    test_hash<Date>();
}

TEST(Hash, TimePoint)
{
    core::mp::foreach<TimePointAll>([]<class T>() {
	    test_hash<T>();
	});
}

TEST(Hash, Duration)
{
    core::mp::foreach<DurationAll>([]<class T>() {
	    test_hash<T>();
	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
