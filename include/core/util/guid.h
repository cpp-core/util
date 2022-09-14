// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <array>
#include <string>

namespace core
{

/**
 * @class Guid
 * @brief Generator for unique identifiers
 *
 *
 * 
 */
class Guid
{
public:
    static constexpr size_t NumberBytes = 16;
    static Guid generate();
    
    Guid() = default;
    Guid(Guid&&) = default;
    Guid(const Guid&) = default;
    Guid& operator=(Guid&&) = default;
    Guid& operator=(const Guid&) = default;

    bool nil() const;
    bool operator==(const Guid& other) const { return m_bytes == other.m_bytes; }
    bool operator!=(const Guid& other) const { return not (*this == other); }
    bool operator<(const Guid& other) const { return m_bytes < other.m_bytes; }

    std::string as_string() const;
    const unsigned char *begin() const { return m_bytes.begin(); }
    const unsigned char *end() const { return m_bytes.end(); }
    
private:
    unsigned char *begin() { return m_bytes.begin(); }
    unsigned char *end() { return m_bytes.end(); }
    std::array<unsigned char, NumberBytes> m_bytes{};
};

}; // core

std::ostream& operator<<(std::ostream& os, const core::Guid& guid);
