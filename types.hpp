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

static_assert(sizeof(float) == 4, "`float` must be 32 bit");
static_assert(sizeof(double) == 8, "`double` must be 64 bit");
static_assert(sizeof(ptrdiff_t) >= sizeof(size_t), "`ssize` must be at least same size as size_t");

#endif /* Include guard */
