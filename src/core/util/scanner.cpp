// Copyright (C) 2022 by Mark Melton
//

#include "core/util/scanner.h"

namespace core::util {

void Scanner::maybe_consume(char c) {
    if (not eos() and *ptr_ == c)
	discard();
}

void Scanner::consume(char c) {
    if (eos() or *ptr_ != c)
	throw_exception("consume: failed to consume {}", c);
    discard();
}

bool Scanner::maybe_consume(std::string_view str) {
    mark_ = ptr_;

    if (remainder().size() < str.size())
	return false;

    const char *pstr = str.data();
    const char *estr = str.data() + str.size();
    while (pstr < estr and *ptr_++ == *pstr++);
    return pstr == estr;
}

void Scanner::consume(std::string_view str) {
    if (not maybe_consume(str))
	throw_exception("consume: failed to find: {}", str);
}

std::string_view Scanner::maybe_consume_to(char delimiter, bool consume_delimiter) {
    mark_ = ptr_;

    const char *begin = ptr_;
    while (ptr_ < end_ and *ptr_ != delimiter)
	++ptr_;
    size_t count = ptr_ - begin;
    if (not eos() and consume_delimiter)
	++ptr_;
    return {begin, count};
}

std::string_view Scanner::consume_to(char delimiter, bool consume_delimiter) {
    auto r = maybe_consume_to(delimiter, consume_delimiter);
    if (r.size() == 0)
	throw_exception("consume_to: empty field before {}", delimiter);
    return r;
}

std::string_view Scanner::consume_quoted(char open, char close) {
    mark_ = ptr_;
    
    consume(open);
    
    const char *begin = ptr_;
    while (ptr_ < end_ and *ptr_ != close)
	++ptr_;
    std::string_view r{begin, size_t(ptr_ - begin)};
    
    consume(close);
    
    return r;
}

}; // core::util



