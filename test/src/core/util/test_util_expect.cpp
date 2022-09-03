// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/util/expect.h"

using namespace core;

TEST(Expect, FailureEQ)
{
    int a = 3;
    int b = 4;
    EXPECT_THROW((ExpectEQ(a, b)), core::expect_exception);

    // try { ExpectEQ(a, b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessEQ)
{
    int a = 3;
    int b = 3;
    EXPECT_NO_THROW((ExpectEQ(a, b)));
}

TEST(Expect, FailureLT)
{
    int a = 3;
    int b = 3;
    EXPECT_THROW((ExpectLT(a, b)), core::expect_exception);

    // try { ExpectLT(a, b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessLT)
{
    int a = 2;
    int b = 3;
    EXPECT_NO_THROW((ExpectLT(a, b)));
}

TEST(Expect, FailureLE)
{
    int a = 4;
    int b = 3;
    EXPECT_THROW((ExpectLE(a, b)), core::expect_exception);

    // try { ExpectLE(a, b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessLE)
{
    int a = 3;
    int b = 3;
    EXPECT_NO_THROW((ExpectLE(a, b)));
}

TEST(Expect, FailureGT)
{
    int a = 3;
    int b = 3;
    EXPECT_THROW((ExpectGT(a, b)), core::expect_exception);

    // try { ExpectGT(a, b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessGT)
{
    int a = 4;
    int b = 3;
    EXPECT_NO_THROW((ExpectGT(a, b)));
}

TEST(Expect, FailureGE)
{
    int a = 2;
    int b = 3;
    EXPECT_THROW((ExpectGE(a, b)), core::expect_exception);

    // try { ExpectGE(a, b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessGE)
{
    int a = 3;
    int b = 3;
    EXPECT_NO_THROW((ExpectGE(a, b)));
}

TEST(Expect, FailureTrue)
{
    int a = 2;
    int b = 3;
    EXPECT_THROW((ExpectTRUE(a == b)), core::expect_exception);

    // try { ExpectTRUE(a == b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessTrue)
{
    int a = 3;
    int b = 3;
    EXPECT_NO_THROW((ExpectTRUE(a == b)));
}

TEST(Expect, FailureFalse)
{
    int a = 3;
    int b = 3;
    EXPECT_THROW((ExpectFALSE(a == b)), core::expect_exception);

    // try { ExpectFALSE(a == b); }
    // catch (core::expect_exception& e)
    // { cout << endl << e.what() << endl << endl; }
}

TEST(Expect, SuccessFalse)
{
    int a = 2;
    int b = 3;
    EXPECT_NO_THROW((ExpectFALSE(a == b)));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
