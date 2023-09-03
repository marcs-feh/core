#ifndef _types_hpp_include_
#define _types_hpp_include_

// TODO: Add flags to disable certain types

#include <cstddef>
#include <cstdint>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using uint    = unsigned int;
using usize   = size_t;
using ssize   = ptrdiff_t;
using byte    = unsigned char;
using rune    = uint32_t;
using uintptr = uintptr_t;

namespace core::limits {
constexpr u8  u8_max  = 0xff;
constexpr u16 u16_max = 0xffff;
constexpr u32 u32_max = 0xffff'ffffULL;
constexpr u64 u64_max = 0xffff'ffff'ffff'ffffULL;

constexpr i8  i8_max  = 0x7f;
constexpr i16 i16_max = 0x7fff;
constexpr i32 i32_max = 0x7fff'ffffLL;
constexpr i64 i64_max = 0x7fff'ffff'ffff'ffffLL;

constexpr i8  i8_min  = -0x80;
constexpr i16 i16_min = -0x8000;
constexpr i32 i32_min = -0x8000'0000LL;
constexpr i64 i64_min = -0x8000'0000'0000'0000LL;
}

static_assert(sizeof(float) == 4, "`float` must be 32 bit");
static_assert(sizeof(double) == 8, "`double` must be 64 bit");
static_assert(sizeof(ptrdiff_t) >= sizeof(size_t), "`ssize` must be at least same size as size_t");

#endif /* Include guard */
