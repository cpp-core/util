// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <string>

namespace core::util {

class Scanner {
public:
    Scanner(std::string_view line)
        : ptr_(line.data())
        , end_(ptr_ + line.size()) {
    }

    std::string_view maybe_consume_to(char delimiter) {
        const char *begin = ptr_;
        while (ptr_ < end_ and *ptr_ != delimiter)
            ++ptr_;
        return {begin, std::size_t(ptr_ - begin)};
    }

private:
    const char *ptr_;
    const char *end_;
};

}; // core::util
