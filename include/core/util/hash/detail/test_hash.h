// Copyright 2021, 2022 by Mark Melton
//

#include <set>
#include "coro/stream/stream.h"
#include "core/util/hash/hash.h"

template<class T>
void test_hash(size_t count) {
    std::set<std::uint64_t> hashes;
    std::set<T> tps;
    auto tpG = coro::Sampler<T>{}();
    for (auto tp : coro::take(std::move(tpG), count)) {
	auto hid = core::hash(tp);
	auto hid_same = core::hash(tp);
	EXPECT_EQ(hid, hid_same);

	if (not tps.contains(tp))
	    EXPECT_FALSE(hashes.contains(hid));
	
	tps.insert(tp);
	hashes.insert(hid);
    }
}
