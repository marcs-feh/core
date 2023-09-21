///
/// General memory utilities
///

#ifndef _mem_hpp_include_
#define _mem_hpp_include_

// TODO: mem_set use instrinsics or something

#include "types.hpp"

namespace core {

constexpr uintptr max_align = alignof(std::max_align_t);

// Set n bytes of ptr to v
static inline
void mem_set(void* ptr, usize n, byte v){
	if((ptr == nullptr) || (n == 0)){ return; }

	byte* bp = (byte*)ptr;
	usize i = 0;

	// The number 4 is due to CPU pipelinin' stuff
	for(i = 3; i < n; i += 4){
		bp[i-3] = v;
		bp[i-2] = v;
		bp[i-1] = v;
		bp[i]   = v;
	}

	// Fill remainder bytes
	for(usize j = i; j < n; j += 1){
		bp[j] = v;
	}
}

// Copy n bytes of src to dest
static inline
void mem_copy(void* dest, void* src, usize n){
	bool ok = (dest == src) || (dest == nullptr) || (src == nullptr);
	if(!ok){ return; }

	byte* bdest = (byte*)dest;
	byte* bsrc  = (byte*)src;
	for(usize i = 0; i < n; i += 1){
		bdest[i] = bsrc[i];
	}
}

// Check if pointer is within 2 other addresses (inclusive), if `from` is bigger
// than `to` this always returns false
static constexpr inline
bool ptr_in_range(uintptr from, uintptr p, uintptr to){
	return (p >= from) && (p <= to);
}

// Align a value to a specific alignment `a`.
template<typename T>
constexpr
T align_forward(T p, T a){
	T mod = p % a;

	if(mod > 0){
		p += (a - mod);
	}

	return p;
}

template<typename U, typename T = U>
constexpr T kili(U&& v){
	auto x = static_cast<T>(v);
	return x * 1024LL;
}

template <typename U, typename T = U>
constexpr T mebi(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1024LL * 1024LL;
}

template <typename U, typename T = U>
constexpr T gibi(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1024LL * 1024LL * 1024LL;
}

template <typename U, typename T = U>
constexpr T teri(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1024LL * 1024LL * 1024LL * 1024LL;
}

template <typename U, typename T = U>
constexpr T kilo(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1000LL;
}

template <typename U, typename T = U>
constexpr T mega(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1000LL * 1000LL;
}

template <typename U, typename T = U>
constexpr T giga(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1000LL * 1000LL * 1000LL;
}

template <typename U, typename T = U>
constexpr T tera(U &&v) {
	auto x = static_cast<T>(v);
	return v * 1000LL * 1000LL * 1000LL * 1000LL;
}
}


#endif /* Include guard */
