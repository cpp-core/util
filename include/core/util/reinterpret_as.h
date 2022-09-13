// Copyright 2019, 2021, 2022 by Mark Melton
//

#include "core/util/common.h"
#include "core/mp/type_name.h"

template<class T>
requires std::is_trivial_v<T> and std::is_standard_layout_v<T>
class reinterpret_as
{
public:
    template<template <class...> class C, class U>
    reinterpret_as(const C<U>& container)
    {
	if ((container.size() * sizeof(U)) % sizeof(T) != 0)
	    throw std::runtime_error
		(fmt::format("bad conversion: {} {}'s is not an intergral number of {}'s",
			     container.size(), core::mp::type_name<U>(),core::mp::type_name<T>()));
	m_size = (container.size() * sizeof(U)) / sizeof(T);
	m_ptr = (const T*)container.data();
	m_end = m_ptr + m_size;
    }

    size_t size() const
    { return m_size; }

    const T *begin() const
    { return m_ptr; }

    const T *end() const
    { return m_end; }

    T operator[](size_t idx)
    { return *(m_ptr + idx); }

    const T *data() const
    { return m_ptr; }

    template<template <class...> class C>
    bool operator==(const C<T>& other) const
    {
	if (size() != other.size())
	    return false;
	return not memcmp(data(), other.data(), sizeof(T) * size());
    }
    
    template<template <class...> class C>
    bool operator!=(const C<T>& other) const
    { return !operator==(other); }
    
private:
    const T *m_ptr, *m_end;
    size_t m_size;
};

template<template <class> class C, class T>
inline bool operator==(const C<T>& a, const reinterpret_as<T>& b)
{ return b.operator==(a); }
    
template<template <class> class C, class T>
inline bool operator!=(const C<T>& a, const reinterpret_as<T>& b)
{ return not b.operator==(a); }
    
