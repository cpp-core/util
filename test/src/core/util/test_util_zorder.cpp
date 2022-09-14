// Copyright 2022 by Mark Melton
//

#include <bit>
#include <gtest/gtest.h>
#include "core/util/zorder.h"
#include "coro/stream/stream.h"

using namespace coro;

static const auto NumberSamples = 64;

TEST(ZOrder, Basic)
{
    int a = 0b100, b = 0b010, c = 0b001;
    auto code64 = zorder64_encode3(a, b, c);
    EXPECT_EQ(code64, 0b100'010'001);

    auto code32 = zorder32_encode3(a, b, c);
    EXPECT_EQ(code32, 0b100'010'001);
}

TEST(ZOrder, EncodeDecode)
{
    auto g = sampler<std::uint32_t>()
	* sampler<std::uint32_t>()
	* sampler<std::uint32_t>()
	| zip()
	| take(NumberSamples);
    for (const auto& [a, b, c] : g) {
	auto a21 = a bitand 0x001F'FFFF;
	auto b21 = b bitand 0x001F'FFFF;
	auto c21 = c bitand 0x001F'FFFF;
	auto code63 = zorder64_encode3(a21, b21, c21);
	
	auto n21 = std::popcount(a21) + std::popcount(b21) + std::popcount(c21);
	EXPECT_EQ(n21, std::popcount(code63));
	
	auto [r21, s21, t21] = zorder64_decode3(code63);
	EXPECT_EQ(a21, r21);
	EXPECT_EQ(b21, s21);
	EXPECT_EQ(c21, t21);

	auto a10 = a bitand 0x000'03FF;
	auto b10 = b bitand 0x000'03FF;
	auto c10 = c bitand 0x000'03FF;
	auto code30 = zorder32_encode3(a21, b21, c21);

	auto n10 = std::popcount(a10) + std::popcount(b10) + std::popcount(c10);
	EXPECT_EQ(n10, std::popcount(code30));
	
	auto [r10, s10, t10] = zorder32_decode3(code30);
	EXPECT_EQ(a10, r10);
	EXPECT_EQ(b10, s10);
	EXPECT_EQ(c10, t10);

    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



