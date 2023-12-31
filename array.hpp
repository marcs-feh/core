//
// Static Array with common element-wise operations.
//

#ifndef _array_hpp_include_
#define _array_hpp_include_

// TODO: use constexpr newton raphson maybe?
#include <cmath>

#include "types.hpp"
#include "utils.hpp"
#include "mem/mem.hpp"

#ifndef NO_BOUNDS_CHECK
#include "assert.hpp"
#define Bounds_Check(expr_) panic_assert((expr_), "Index out of bounds")
#else
#define Bounds_Check(expr_)
#endif

namespace core {

template<typename T, usize N>
struct Array {
	T data[N];

	constexpr
	usize len() const { return N; }

	constexpr
	T& operator[](usize idx){
		// Bounds_Check(idx < N);
		return data[idx];
	}

	constexpr
	const T& operator[](usize idx) const{
		// Bounds_Check(idx < N);
		return data[idx];
	}

	template<typename U>
	constexpr
	Array<U, N> as_type() const{
		Array<U, N> a;
		for(usize i = 0; i < N; i += 1){
			a[i] = static_cast<U>(data[i]);
		}
		return a;
	}


	static_assert(N > 0, "Array of size 0 not allowed");
	static_assert((N * sizeof(T)) < kili(1), "Array exceeds max_array_size");
};

/// Vector operations ///

template<typename T, usize N>
constexpr
Array<T,N> operator+(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] + b.data[i];
	}
	return v;
}

template<typename T, usize N>
constexpr
Array<T,N> operator-(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] - b.data[i];
	}
	return v;
}

template<typename T, usize N>
constexpr
Array<T,N> operator/(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		// core::panic_assert(b.data[i] != 0, "Division by zero");
		v.data[i] = a.data[i] / b.data[i];
	}
	return v;
}

template<typename T, usize N>
constexpr
Array<T,N> operator*(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] * b.data[i];
	}
	return v;
}

template<typename T, usize N>
constexpr
bool operator==(const Array<T,N>& a, const Array<T,N>& b){
	for(usize i = 0; i < N; i += 1){
		if(a.data[i] != b.data[i]){ return false; }
	}
	return true;
}

template<typename T, usize N>
constexpr
bool operator!=(const Array<T,N>& a, const Array<T,N>& b){
	return !(a == b);
}

/// Scalar operations ///

template<typename T, usize N, typename S>
constexpr
Array<T,N> operator+(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] + T(b);
	}
	return v;
}

template<typename T, usize N, typename S>
constexpr
Array<T,N> operator-(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] - b;
	}
	return v;
}

template<typename T, usize N, typename S>
constexpr
Array<T,N> operator*(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] * b;
	}
	return v;
}

template<typename T, usize N, typename S>
constexpr
Array<T,N> operator/(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] / b;
	}
	return v;
}

namespace {

template<typename T, usize N, usize I, typename U>
constexpr
void fill_arr_with_param_pack(Array<T, N>& v, U&& elem){
	static_assert(I < N, "Out of bounds");
	v[I] = static_cast<T>(elem);
}

template<typename T, usize N, usize I = 0, typename U,typename... Args>
constexpr
void fill_arr_with_param_pack(Array<T, N>& v, U&& elem, Args&& ...indices){
	static_assert(I < N, "Out of bounds");
	v[I] = static_cast<T>(elem);
	fill_arr_with_param_pack<T, N, I+1>(v, forward<Args>(indices)...);
}

}

template<typename T, usize N, typename U>
constexpr
auto swizzle(const Array<T, N>& v, U&& idx){
	Array<T, 1> res;
	res[0] = v[idx];
	return res;
}

template<typename T, usize N, typename... Index>
constexpr
auto swizzle(const Array<T, N>& v, Index&& ...indices){
	constexpr usize L  = sizeof...(indices);
	Array<usize, L> idxv;
	Array<T, L> res;

	fill_arr_with_param_pack(idxv, indices...);
	for(usize i = 0; i < L; i += 1){
		res[i] = v[idxv[i]];
	}

	return res;
}


template<typename T, usize N>
constexpr
T sum(const Array<T,N>& v){
	T s{0};
	for(usize i = 0; i < N; i += 1){
		s += v.data[i];
	}
	return s;
}

template<typename T, usize N>
auto mag(const Array<T,N>& v){
	auto s = sum(v * v);
	return std::sqrt(s);
}


template<typename T, usize N, typename VecFunc>
constexpr
Array<T, N> map(VecFunc&& f, const Array<T,N>& v){
	Array<T, N> a;
	for(usize i = 0; i < N; i += 1){
		// core::panic_assert(b.data[i] != 0, "Division by zero");
		a.data[i] = f(v.data[i]);
	}
	return a;
}

}

#endif /* Include guard */
