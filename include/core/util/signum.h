// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

template <class T>
constexpr int signum(T val)
{ return (T(0) < val) - (val < T(0)); }

