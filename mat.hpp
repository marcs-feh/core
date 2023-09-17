#ifndef _mat_hpp_include_
#define _mat_hpp_include_

#include "mem/mem.hpp"
#include "types.hpp"
#include "array.hpp"


namespace core {
template<typename T, usize H, usize W>
struct Mat {
	using Row = Array<T, W>;
	using Col = Array<T, H>;
	struct Coord {
	  usize row;
	  usize col;
	};

	T data[H * W];

	constexpr
	usize height() const { return H; }

	constexpr
	usize width() const { return W; }

	constexpr
	Row row(usize idx) const {
		Row r;
		for(usize i = 0; i < W; i += 1){
			r[i] = at(idx, i);
		}
		return r;
	}

	constexpr
	Col col(usize idx) const {
		Col c;
		for(usize i = 0; i < W; i += 1){
			c[i] = at(i, idx);
		}
		return c;
	}

	constexpr
	T& at(usize row, usize col){
		// Bounds_Check(row < H);
		// Bounds_Check(col < W);
		return data[(col * H) + row];
	}

	constexpr
	const T& at(usize row, usize col) const {
		// Bounds_Check(row < H);
		// Bounds_Check(col < W);
		return data[(col * H) + row];
	}

	static_assert((W * H) < kili(16), "Matrix too big, adjust this assert or use BigMat");
};

template<typename T, usize H, usize W>
constexpr
Mat<T, H, W> transpose(const Mat<T,W,H>& m){
	Mat<T, H, W> t;
	for(usize row = 0; row < H; row += 1){
		for(usize col = 0; col < W; col += 1){
			t.at(row, col) = m.at(col, row);
		}
	}
	return t;
}

template<typename T, usize H, usize W>
constexpr
bool operator==(const Mat<T,H,W>& a, const Mat<T,H,W>& b){
	for(usize i = 0; i < (H*W); i += 1){
		if(a.data[i] != b.data[i]){ return false; }
	}
	return true;
}

template<typename T, usize H, usize W>
constexpr
T sum(const Mat<T,H,W>& m){
	T s{0};
	for(usize i = 0; i < (W*H); i += 1){
		s += m.data[i];
	}
	return s;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator+(const Mat<T,H,W>& a, const Mat<T,H,W>& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] + b.data[i];
	}
	return m;
}


template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator-(const Mat<T,H,W>& a, const Mat<T,H,W>& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] - b.data[i];
	}
	return m;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator*(const Mat<T,H,W>& a, const Mat<T,H,W>& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] * b.data[i];
	}
	return m;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator/(const Mat<T,H,W>& a, const Mat<T,H,W>& b){
	// TODO: div by zero
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] / b.data[i];
	}
	return m;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator+(const Mat<T,H,W>& a, const T& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] + b;
	}
	return m;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator-(const Mat<T,H,W>& a, const T& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] - b;
	}
	return m;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator*(const Mat<T,H,W>& a, const T& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] * b;
	}
	return m;
}


template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator/(const Mat<T,H,W>& a, const T& b){
	Mat<T,H,W> m;
	for(usize i = 0; i < (H*W); i += 1){
		m.data[i] = a.data[i] / b;
	}
	return m;
}

template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator+(const T& a, const Mat<T,H,W>& b){ return b + a; }
template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator-(const T& a, const Mat<T,H,W>& b){ return b - a; }
template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator*(const T& a, const Mat<T,H,W>& b){ return b * a; }
template<typename T, usize H, usize W>
constexpr
Mat<T,H,W> operator/(const T& a, const Mat<T,H,W>& b){ return b / a; }

}

#endif /* Include guard */
