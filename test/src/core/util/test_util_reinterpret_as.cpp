// Copyright 2019, 2021, 2022 by Mark Melton
//

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
    auto g = coro::sampler<size_t>(1, 64)
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
    string str{"ABCDE"};
    EXPECT_THROW(reinterpret_as<int> ivec{str};, std::runtime_error);

    uints ivec{1,2,3};
    EXPECT_THROW(reinterpret_as<real64> rvec{ivec};, std::runtime_error);
}

#define CODE(A,B) check<A,B>();
#define CODE_SEQ(A) CODE(CORE_PP_HEAD_SEQ(A), CORE_PP_SECOND_SEQ(A))
#define TYPES() (char, int8, uint8, int, uint, int64, uint64, real32, real64)
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



