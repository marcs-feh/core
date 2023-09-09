#ifndef _types_hpp_include_
#define _types_hpp_include_

#include <cstddef>
#include <cfloat>
#include <cstdint>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#ifndef NO_FLOATS
#ifndef NO_FLOAT16
using f16 = _Float16;
static_assert(sizeof(f16) == 2, "`f16` must be 16 bit");
#endif

#ifndef NO_FLOAT16
using f32 = float;
static_assert(sizeof(f32) == 4, "`f32` must be 32 bit");
#endif

#ifndef NO_FLOAT16
using f64 = double;
static_assert(sizeof(f64) == 8, "`f64` must be 64 bit");
#endif
#endif

using uint    = unsigned int;
using usize   = size_t;

#ifndef NO_SIGNED_SIZE
using ssize   = ptrdiff_t;
static_assert(sizeof(ptrdiff_t) >= sizeof(size_t), "`ssize` must be at least same size as size_t");
#endif

using byte    = unsigned char;
using rune    = uint32_t;
using uintptr = uintptr_t;

// boolean types for specific memory alignment
using b8  = uint8_t;
using b16 = uint16_t;
using b32 = uint32_t;
using b64 = uint64_t;

namespace core::limits {
constexpr u8  u8_max  = 0xffULL;
constexpr u16 u16_max = 0xffffULL;
constexpr u32 u32_max = 0xffff'ffffULL;
constexpr u64 u64_max = 0xffff'ffff'ffff'ffffULL;

constexpr i8  i8_max  = 0x7fLL;
constexpr i16 i16_max = 0x7fffLL;
constexpr i32 i32_max = 0x7fff'ffffLL;
constexpr i64 i64_max = 0x7fff'ffff'ffff'ffffLL;

constexpr i8  i8_min  = -0x80LL;
constexpr i16 i16_min = -0x8000LL;
constexpr i32 i32_min = -0x8000'0000LL;
constexpr i64 i64_min = -0x8000'0000'0000'0000LL;
}

#endif /* Include guard */
