// Copyright (C) 2017, 2018, 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include <fmt/format.h>
#include "core/util/exception.h"
#include "core/util/expect.h"

using std::cerr;
using std::cout;
using std::cin;
using std::endl;

using std::list;
using std::map;
using std::set;
using std::vector;

using string = std::string;
using strings = std::vector<string>;
using string_view = std::string_view;
using string_views = std::vector<string_view>;
using namespace std::literals::string_literals;

using byte = std::byte;
using bytes = vector<std::byte>;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using int128 = __int128;
using intmax = std::intmax_t;
using ints = std::vector<int>;
using int32s = std::vector<int32>;
using int64s = std::vector<int64>;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using uint128 = unsigned __int128;
using uintmax = std::uintmax_t;
using uint = unsigned int;
using uints = std::vector<uint>;
using uint8s = std::vector<uint8>;
using uint16s = std::vector<uint16>;
using uint32s = std::vector<uint32>;
using uint64s = std::vector<uint64>;

using real32 = float;
using real64 = double;
using real128 = long double;
using real = real64;
using reals = std::vector<real>;
using real32s = std::vector<real32>;
using real64s = std::vector<real64>;

using index_t = std::ptrdiff_t;
using index_ts = std::vector<index_t>;
using size_t = std::size_t;
using size_ts = std::vector<size_t>;
using ptrdiff_t = std::ptrdiff_t;

using namespace fmt::literals;
