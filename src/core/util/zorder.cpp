// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#include "core/util/zorder.h"

// Return the low-order 21-bits of **data** exploded into 63 bits by
// inserting two zero-bits between each.
std::uint64_t zorder64_encode_by3(std::uint64_t data) {
    data = data bitand 0x0000'0000'001F'FFFFul;
    // .... .... .... .... | .... .... .... .... | .... .... ...4 3210 | fedc ba98 7654 3210
    data = (data bitor (data << 32)) bitand 0x001F'0000'0000'FFFFul;
    // .... .... ...4 3210 | .... .... .... .... | .... .... .... .... | fedc ba98 7654 3210
    data = (data bitor (data << 16)) bitand 0x001F'0000'FF00'00FFul;
    // .... .... ...4 3210 | .... .... .... .... | fedc ba98 .... .... | .... .... 7654 3210
    data = (data bitor (data << 8)) bitand 0x100F'00F0'0F00'F00Ful;
    // ...4 .... .... 3210 | .... .... fedc .... | .... ba98 .... .... | 7654 .... .... 3210
    data = (data bitor (data << 4)) bitand 0x10C3'0C30'C30C'30C3ul;
    // ...4 .... 32.. ..10 | .... fe.. ..dc .... | ba.. ..98 .... 76.. | ..54 .... 32.. ..10
    data = (data bitor (data << 2)) bitand 0x1249'2492'4924'9249ul;
    // ...4 ..3. .2.. 1..0 | ..f. .e.. d..c ..b. | .a.. 9..8 ..7. .6.. | 5..4 ..3. .2.. 1..0
    return data;
}

// Return every third bit of **code** collapsed into 21 low-order bits.
std::uint64_t zorder64_decode_by3(std::uint64_t code) {
    code = code bitand 0x1249'2492'4924'9249ul;
    // ...4 ..3. .2.. 1..0 | ..f. .e.. d..c ..b. | .a.. 9..8 ..7. .6.. | 5..4 ..3. .2.. 1..0
    code = (code bitor (code >> 2)) bitand 0x10C3'0C30'C30C'30C3ul;
    // ...4 .... 32.. ..10 | .... fe.. ..dc .... | ba.. ..98 .... 76.. | ..54 .... 32.. ..10
    code = (code bitor (code >> 4)) bitand 0x100F'00F0'0F00'F00Ful;
    // ...4 .... .... 3210 | .... .... fedc .... | .... ba98 .... .... | 7654 .... .... 3210
    code = (code bitor (code >> 8)) bitand 0x001F'0000'FF00'00FFul;
    // .... .... ...4 3210 | .... .... .... .... | fedc ba98 .... .... | .... .... 7654 3210
    code = (code bitor (code >> 16)) bitand 0x001F'0000'0000'FFFFul;
    // .... .... ...4 3210 | .... .... .... .... | .... .... .... .... | fedc ba98 7654 3210
    code = (code bitor (code >> 32)) bitand 0x0000'0000'001F'FFFFul;
    // .... .... .... .... | .... .... .... .... | .... .... ...4 3210 | fedc ba98 7654 3210
    return code;
}

std::uint64_t zorder64_encode3(std::uint32_t a, std::uint32_t b, std::uint32_t c) {
    return (zorder64_encode_by3(a) << 2)
	bitor (zorder64_encode_by3(b) << 1)
	bitor zorder64_encode_by3(c);
}

std::tuple<std::uint32_t,std::uint32_t,std::uint32_t> zorder64_decode3(std::uint64_t x) {
    return { zorder64_decode_by3(x >> 2), zorder64_decode_by3(x >> 1), zorder64_decode_by3(x) };
}

// Return the low-order 10-bits of **data** exploded into 30 bits by
// inserting two zero-bits between each.
std::uint32_t zorder32_encode_by3(std::uint32_t data) {
    data = data bitand 0x0000'03FFul;
    // .... .... .... .... | .... ..98 7654 3210
    data = (data bitor (data << 16)) bitand 0x0300'00FFul;
    // .... ..98 .... .... | .... .... 7654 3210
    data = (data bitor (data << 8)) bitand 0x0300'F00Ful;
    // .... ..98 .... .... | 7654 .... .... 3210
    data = (data bitor (data << 4)) bitand 0x030C'30C3ul;
    // .... ..98 .... 76.. | ..54 .... 32.. ..10
    data = (data bitor (data << 2)) bitand 0x0924'9249ul;
    // .... 9..8 ..7. .6.. | 5..4 ..3. .2.. 1..0
    return data;
}

// Return every third bit of **code** collapsed into 10 low-order
// bits.
std::uint32_t zorder32_decode_by3(std::uint32_t code) {
    code = code bitand 0x0924'9249ul;
    // .... 9..8 ..7. .6.. | 5..4 ..3. .2.. 1..0
    code = (code bitor (code >> 2)) bitand 0x030C'30C3ul;
    // .... ..98 .... 76.. | ..54 .... 32.. ..10
    code = (code bitor (code >> 4)) bitand 0x0300'F00Ful;
    // .... ..98 .... .... | 7654 .... .... 3210
    code = (code bitor (code >> 8)) bitand 0x0300'00FFul;
    // .... ..98 .... .... | .... .... 7654 3210
    code = (code bitor (code >> 16)) bitand 0x0000'03FFul;
    // .... .... .... .... | .... ..98 7654 3210
    return code;
}

std::uint32_t zorder32_encode3(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    return (zorder32_encode_by3(a) << 2)
	bitor (zorder32_encode_by3(b) << 1)
	bitor zorder32_encode_by3(c);
}

std::tuple<std::uint16_t,std::uint16_t,std::uint16_t> zorder32_decode3(std::uint32_t code) {
    return { zorder32_decode_by3(code >> 2),
	zorder32_decode_by3(code >> 1),
	zorder32_decode_by3(code) };
}

