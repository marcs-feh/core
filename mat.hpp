#ifndef _mat_hpp_include_
#define _mat_hpp_include_

#include "types.hpp"
#include "array.hpp"

namespace core {
template<typename T, usize N, usize M>
struct Mat {
	using Row = Array<T, M>;
	using Col = Array<T, N>;

	T data[N * M];

	constexpr
	usize height() const { return N; }

	constexpr
	usize width() const { return M; }

	constexpr
	Row row(usize idx) const {
		Row r;
		for(usize i = 0; i < M; i += 1){
			r[i] = data[(idx * M) + i];
		}
		return r;
	}

	constexpr
	Col col(usize idx) const {
		Col c;
		for(usize i = 0; i < N; i += 1){
			c[i] = data[(i * M) + idx];
		}
		return c;
	}

	constexpr
	T& at(usize row, usize col){
		// Bounds_Check(row < N);
		// Bounds_Check(col < M);
		return data[(row * M) + col];
	}

	constexpr
	const T& at(usize row, usize col) const {
		// Bounds_Check(row < N);
		// Bounds_Check(col < M);
		return data[(row * M) + col];
	}
};

template<typename T, usize N, usize M>
constexpr
Mat<T, N, M> transpose(const Mat<T,M,N>& m){
	Mat<T, N, M> t;
	for(usize row = 0; row < N; row += 1){
		for(usize col = 0; col < M; col += 1){
			t.at(row, col) = m.at(col, row);
		}
	}
	return t;
}

template<typename T, usize N, usize M>
constexpr
bool operator==(const Mat<T,N,M>& a, const Mat<T,N,M>& b){
	for(usize i = 0; i < (N*M); i += 1){
		if(a.data[i] != b.data[i]){ return false; }
	}
	return true;
}

template<typename T, usize N, usize M>
constexpr
T sum(const Mat<T,N,M>& m){
	T s{0};
	for(usize i = 0; i < (M*N); i += 1){
		s += m.data[i];
	}
	return s;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator+(const Mat<T,N,M>& a, const Mat<T,N,M>& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] + b.data[i];
	}
	return m;
}


template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator-(const Mat<T,N,M>& a, const Mat<T,N,M>& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] - b.data[i];
	}
	return m;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator*(const Mat<T,N,M>& a, const Mat<T,N,M>& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] * b.data[i];
	}
	return m;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator/(const Mat<T,N,M>& a, const Mat<T,N,M>& b){
	// TODO: div by zero
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] / b.data[i];
	}
	return m;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator+(const Mat<T,N,M>& a, const T& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] + b;
	}
	return m;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator-(const Mat<T,N,M>& a, const T& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] - b;
	}
	return m;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator*(const Mat<T,N,M>& a, const T& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] * b;
	}
	return m;
}


template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator/(const Mat<T,N,M>& a, const T& b){
	Mat<T,N,M> m;
	for(usize i = 0; i < (N*M); i += 1){
		m.data[i] = a.data[i] / b;
	}
	return m;
}

template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator+(const T& a, const Mat<T,N,M>& b){ return b + a; }
template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator-(const T& a, const Mat<T,N,M>& b){ return b - a; }
template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator*(const T& a, const Mat<T,N,M>& b){ return b * a; }
template<typename T, usize N, usize M>
constexpr
Mat<T,N,M> operator/(const T& a, const Mat<T,N,M>& b){ return b / a; }


}

#endif /* Include guard */
