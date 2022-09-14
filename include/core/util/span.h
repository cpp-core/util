// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#pragma once
#include <cstdint>
#include <fmt/format.h>
#include <limits>
#include <span>

namespace std {

template<class T>
T& at(std::span<T>& s, size_t index) {
    if (index < s.size())
	return s[index];
    throw std::range_error
	(fmt::format("span: index out of range {} not less than {}", index, s.size()));
}

template<class T>
std::span<T> shift(const std::span<T>& s, std::ptrdiff_t pos) {
    size_t n = std::abs(pos);
    if (n > s.size())
	throw std::out_of_range{"shift(span s, index_t pos): abs(pos) exceeds size"};
    return std::span<T>{ s.data() + std::max(std::ptrdiff_t{0}, pos), s.size() - n };
}

template<typename T>
std::span<T> rtrim(const std::span<T>& s, size_t n)
{
    return std::span<T>{ s.data(), std::max(size_t{0}, s.size() - n) };
};

template<typename T>
std::span<T> ltrim(const std::span<T>& s, size_t n)
{
    return std::span<T>{ s.data() + n, std::max(size_t{0}, s.size() - n) };
};

}; // std

