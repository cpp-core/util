// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include <deque>
#include "core/common.h"
#include "core/mp/same.h"

namespace core::sbs {

// Return true iff T is a template of type C
template<class T, template<class...> class C>
constexpr bool is_kind = core::mp::is_same_template_v<T, C>;

// Concept for sequence containers that can be serilized.
template<class T>
concept SequenceContainer = is_kind<T, std::vector> ||
    is_kind<T, std::list> ||
    is_kind<T, std::deque>;

// Concept for associtive containers that can be serialized.
template<class T>
concept AssociativeContainer = is_kind<T, std::set> ||
    is_kind<T, std::map>;

// Concept for containers that can be serlialized.
template<class T>
concept Container = SequenceContainer<T> or AssociativeContainer<T>;

// Concept for pod-like types that can be serialized.
template<class T>
concept PodLike = std::is_integral_v<T> or std::is_floating_point_v<T>;

}; // core::sbs

