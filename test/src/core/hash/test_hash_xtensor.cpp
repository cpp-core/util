// Copyright 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/hash/hash_xtensor.h"
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"
#include "core/hash/test_hash.h"

TEST(Hash, XArray)
{
    xt::xarray<int> x = {{1, 2, 3}, {4, 5, 6}};
    auto hid = core::hash(x);
    x(0,0) = 0;
    auto hid_other = core::hash(x);
    EXPECT_NE(hid, hid_other);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
