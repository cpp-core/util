// Copyright (C) 2022 by Mark Melton
//

#pragma once
#include <nlohmann/json.hpp>
#include "core/util/exception.h"

using json = nlohmann::json;

template<class T>
T get_or_else(const json& j, const std::string& key, const T& value) {
    if (j.contains(key)) return j.at(key).get<T>();
    return value;
}

template<class T>
T get(const json& j, const std::string& key) {
    if (j.contains(key)) return j.at(key).get<T>();
    throw core::runtime_error("failed to find key {} in json: {}", key, j.dump());
}

inline auto must_contain(const json& j, const std::string& key) {
    if (not j.contains(key))
	throw core::runtime_error("failed to find key {} in json {}", key, j.dump());
    return j.at(key);
}

