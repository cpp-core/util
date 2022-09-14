// Copyright 2019, 2021, 2022 by Mark Melton
//

#include <cstdint>
#include <gtest/gtest.h>
#include "core/pp/seq.h"
#include "core/pp/map.h"
#include "core/pp/product.h"
#include "core/util/reinterpret_as.h"
#include "coro/stream/stream.h"

static const size_t NumberSamples = 16;

using namespace coro;

template<class T, class U>
void check()
{
    auto g = coro::sampler<std::size_t>(1u, 64u)
	* coro::sampler<T>()
	| sampler_vector();
    
    size_t count{0};
    for (auto vec :  std::move(g) | coro::take(NumberSamples)) {
	if (vec.size() % sizeof(U) != 0)
	    continue;
	
	reinterpret_as<U> uvec{vec};
	reinterpret_as<T> tvec{uvec};
	EXPECT_EQ(tvec, vec);

	std::vector<T> new_vec;
	for (auto idx : tvec)
	    new_vec.push_back(idx);
	EXPECT_EQ(new_vec, vec);

	++count;
	if (count >= NumberSamples)
	    break;
    }
}

TEST(ReinterpretAs, Exception)
{
    std::string str{"ABCDE"};
    EXPECT_THROW(reinterpret_as<int> ivec{str};, std::runtime_error);

    std::vector<int> ivec{1,2,3};
    EXPECT_THROW(reinterpret_as<double> rvec{ivec};, std::runtime_error);
}

#define CODE(A,B) check<A,B>();
#define CODE_SEQ(A) CODE(CORE_PP_HEAD_SEQ(A), CORE_PP_SECOND_SEQ(A))
#define TYPES() (char, std::int8_t, std::uint8_t, int, unsigned int, std::int64_t, std::uint64_t, float, double)
#define PRODUCT() CORE_PP_EVAL_CARTESIAN_PRODUCT_SEQ(TYPES(), TYPES())

TEST(ReinterpretAs, TypeToType)
{
    CORE_PP_EVAL_MAP_SEQ(CODE_SEQ, PRODUCT());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



