// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <any>
#include <fmt/format.h>
#include <map>
#include <typeindex>
#include "core/mp/type_name.h"

namespace core {
inline namespace util {
       
// TypeMap - A map-like container that maps types to values. Each
// unique type functions as a unique key and is associated with a
// single value of that type.
class TypeMap {
public:
    using Map = std::map<std::type_index, std::any>;

    // Construct an empty map.
    TypeMap() {
    }

    // Construct a map with the given values.
    template<class... Ts>
    requires (sizeof...(Ts) > 0)
    TypeMap(Ts&& ...args) {
	insert(std::forward<Ts>(args)...);
    }

    // Destruct the map.
    ~TypeMap() {
    }

    // Return the number of entries in the map.
    std::size_t size() const {
	return properties_.size();
    }

    // Insert the given values into the map. Throw an exception if any
    // type is already in the map.
    template<class T, class... Ts>
    void insert(T&& arg, Ts&& ...args) {
	if (auto iter = properties_.find(typeid(T)); iter != properties_.end())
	    throw std::runtime_error(fmt::format("Attempt to insert duplicate type: {}",
						 core::mp::type_name<T>()));
	properties_[typeid(T)] = std::forward<T>(arg);
	if constexpr (sizeof...(Ts) > 0)
	    insert(std::forward<Ts>(args)...);
    }

    // Insert the given values into the map replacing any existing
    // values.
    template<class T, class... Ts>
    void upsert(T&& arg, Ts&& ...args) {
	properties_[typeid(T)] = std::forward<T>(arg);
	if constexpr (sizeof...(Ts) > 0)
	    insert(std::forward<Ts>(args)...);
    }

    // Remove the specified types ignoring types that are not in the
    // map.
    template<class T, class... Ts>
    void remove() {
	properties_.erase(typeid(T));
	if constexpr (sizeof...(Ts) > 0)
	    remove<Ts...>();
    }
    
    // Remove the given values ignoring values that are not in the map.
    template<class T, class... Ts>
    void remove(T&& arg, Ts&& ...args) {
	remove<T, Ts...>();
    }

    // Erase all map entries.
    void clear() {
	properties_.clear();
    }

    // Return true if map contains type `T`; otherwise, return false.
    template<class T>
    bool contains() const {
	return properties_.contains(typeid(T));
    }

    // Return true if map contains `value`; otherwise, return false.
    template<class T>
    bool contains(const T& value) const {
	if (auto iter = properties_.find(typeid(T)); iter != properties_.end())
	    return std::any_cast<T>(iter->second) == value;
	return false;
    }

    // // TODO: Need to rename this function.
    // template<class T>
    // bool may_contain_value(const T& value) const {
    // 	return not has_key<T>() or contains_value(value);
    // }

    // Return a reference to the value for type `T` if it is in the
    // map; otherwise; throw an exception.
    template<class T>
    T& get() {
	if (auto iter = properties_.find(typeid(T)); iter != properties_.end())
	    return std::any_cast<T&>(iter->second);
	throw std::runtime_error(fmt::format("TypeMap: no `{}` in map", core::mp::type_name<T>()));
    }

    // Return the value for type `T` if it is in the map; otherwise;
    // throw an exception.
    template<class T>
    const T& get() const {
	if (auto iter = properties_.find(typeid(T)); iter != properties_.end())
	    return std::any_cast<const T&>(iter->second);
	throw std::runtime_error
	    (fmt::format("TypeMap: no `{}` in map", core::mp::type_name<T>()));
    }

    // Return the value for type `T` if it is in the map; otherwise,
    // return `value`.
    template<class T>
    T get_or_else(T value) const {
	if (contains<T>()) return get<T>();
	else return value;
    }

    // Return a string representation of the map.
    std::string repr() const;

    const Map& items() const {
	return properties_;
    }

private:
    Map properties_;
};

using TypeMaps = std::vector<TypeMap>;

}; // type
}; // core
