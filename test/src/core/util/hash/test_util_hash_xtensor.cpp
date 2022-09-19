// Copyright 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"
#include "core/util/hash/core.h"
#include "core/util/hash/xtensor.h"
#include "core/util/hash/detail/test_hash.h"

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
