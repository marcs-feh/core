#ifndef _array_hpp_include_
#define _array_hpp_include_

#include "types.hpp"

#ifndef NO_BOUNDS_CHECK
#include "assert.hpp"
#define Bounds_Check(expr_) panic_assert((expr_), "Index out of bounds")
#else
#define Bounds_Check(expr_)
#endif

namespace core {

constexpr usize max_array_size = 8192;

template<typename T, usize N>
struct Array {
	T data[N];

	usize len() const { return N; }

	T& operator[](usize idx){
		Bounds_Check(idx < N);
		return data[idx];
	}
	const T& operator[](usize idx) const{
		Bounds_Check(idx < N);
		return data[idx];
	}

	static_assert(N > 0, "Array of size 0 not allowed");
	static_assert(N < max_array_size, "Array exceeds max_array_size");
};

/// Vector operations ///

template<typename T, usize N>
Array<T,N> operator+(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] + b.data[i];
	}
	return v;
}

template<typename T, usize N>
Array<T,N> operator-(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] - b.data[i];
	}
	return v;
}

template<typename T, usize N>
Array<T,N> operator/(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		// core::panic_assert(b.data[i] != 0, "Division by zero");
		v.data[i] = a.data[i] / b.data[i];
	}
	return v;
}

template<typename T, usize N>
Array<T,N> operator*(const Array<T,N>& a, const Array<T,N>& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] * b.data[i];
	}
	return v;
}

template<typename T, usize N>
bool operator==(const Array<T,N>& a, const Array<T,N>& b){
	for(usize i = 0; i < N; i += 1){
		if(a.data[i] != b.data[i]){ return false; }
	}
	return true;
}

/// Scalar operations ///

template<typename T, usize N, typename S>
Array<T,N> operator+(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] + T(b);
	}
	return v;
}

template<typename T, usize N, typename S>
Array<T,N> operator-(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] - b;
	}
	return v;
}

template<typename T, usize N, typename S>
Array<T,N> operator*(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] * b;
	}
	return v;
}

template<typename T, usize N, typename S>
Array<T,N> operator/(const Array<T,N>& a, const S& b){
	Array<T, N> v;
	for(usize i = 0; i < N; i += 1){
		v.data[i] = a.data[i] / b;
	}
	return v;
}

template<typename T, usize N>
T sum(const Array<T,N>& v){
	T s{0};
	for(usize i = 0; i < N; i += 1){
		s += v.data[i];
	}
	return s;
}

// TODO: Concepts?

template<typename T, usize N, typename VecFunc>
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
