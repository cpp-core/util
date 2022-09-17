// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <fmt/format.h>
#include <string>

namespace core::util {

/// Simple scanner for strings.
///
/// `point` - the current location of the scanner
/// `eos` - one past the last character of the string
class Scanner {
public:
    /// Create a scanner for the given `line`
    Scanner(std::string_view line)
        : line_(line)
	, mark_(line_.data())
	, ptr_(line_.data())
	, end_(ptr_ + line_.size()) {
    }

    /// Return true if point is at eos, false otherwise.
    bool eos() const { return ptr_ == end_; }
    
    /// Return the character at point.
    char peek() const { return *ptr_; }

    /// Return a view of the consumed characters.
    std::string_view consumed() const { return {line_.data(), std::size_t(ptr_ - line_.data())}; }
    
    /// Return a view of the remaining characters.
    std::string_view remainder() const { return {ptr_, std::size_t(end_ - ptr_)}; }

    /// Return the character at point and advance point.
    char consume() { return *ptr_++; }

    /// Advance point.
    void discard() { ++ptr_; }

    /// Advance point if point is at character `c`;
    void maybe_consume(char c);

    /// If point is at character `c`, advance point; otherwise, throw
    /// an exception.
    void consume(char c);

    /// Return true and advance point if point is at `str`; otherwise,
    /// return false.
    bool maybe_consume(std::string_view str);

    /// Advance point if point is at `str`; otherwise, throw an
    /// exception.
    void consume(std::string_view str);

    /// Advance point to (or past if `consume_delimiter` is true)
    /// `delimiter` or to eof and return a view of the consumed
    /// characters (possibly empty).
    std::string_view maybe_consume_to(char delimiter, bool consume_delimiter = true);

    /// Advance point to (or past if `consume_delimiter` is true)
    /// `delimiter` or to eof and return a view of the consumed
    /// characters, unless no characters are consumed in which case
    /// throw and exception.
    std::string_view consume_to(char delimiter, bool consume_delimiter = true);

    /// Advance point from the `open` character to the `close`
    /// character and return a view (possibly empty) of the consumed
    /// characters (not including the delimiters);
    std::string_view consume_quoted(char open = '"', char close = '"');

    /// Advance iteratively through a sequence starting with the `open`
    /// character, ending with the `close` character and delimited by
    /// `,`. Call `func` for each element of the sequence in turn with
    /// the parser positioned at the first character of the
    /// element. `func` must leave the parser positioned at the
    /// character just after element (i.e. either `,` or `close`) after
    /// each invokation.
    template<class F>
    void consume_sequence(char open, char close, F&& func) {
	consume(open);
	while (peek() != close) {
	    func(*this);
	    maybe_consume(',');
	}
	consume(close);
    }

    /// Advance iteratively through a dictionary starting with the
    /// `open` character, ending with the `close` character, key-values
    /// separarated by `delim` and entries delimited by `,`. Call `func`
    /// for each value of the dictionary in turn with both a view of
    /// the key and the parser positioned at the first character of the
    /// value. `func` must leave the parser positioned at the
    /// character just after value (i.e. either `,` or `close`).
    template<class F>
    void consume_dict(char open, char close, char delim, F&& func) {
	consume(open);
	while (peek() != close) {
	    auto key = consume_quoted();
	    consume(delim);
	    func(key, *this);
	    maybe_consume(',');
	}
	consume(close);
    }
    
private:
    template<class... Args>
    void throw_exception(std::string_view fmt, Args&&... args) {
	auto e0 = fmt::format(fmt::runtime(fmt), args...);
	auto e1 = fmt::format("input: {}", line_);
	auto e2 = fmt::format("mark : {}^", std::string(mark_ - line_.data(), ' '));
	auto e3 = fmt::format("point: {}^", std::string(ptr_ - line_.data(), ' '));
	throw std::runtime_error(fmt::format("\n{}\n{}\n{}\n{}\n", e0, e1, e2, e3));
    }

    std::string_view line_;
    const char *mark_;
    const char *ptr_;
    const char *end_;
};

}; // core::util
