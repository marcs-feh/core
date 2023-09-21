#ifndef _mat_hpp_include_
#define _mat_hpp_include_

#include "mem/mem.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "array.hpp"

namespace core {
template<typename T, usize W, usize H>
struct CMat {
	using Col = Array<T, H>;
	using Row = Array<T, W>;

	Col data[W];

	constexpr
	usize height() const { return H; }

	constexpr
	usize width() const { return W; }

	constexpr
	Col col(usize idx) const {
		// Bounds_Check(idx < W);
		return data[idx];
	}

	constexpr
	Row row(usize idx) const {
		// Bounds_Check(idx < H);
		Row r;
		for(usize i = 0; i < W; i += 1){
			r[i] = data[i][idx];
		}
		return r;
	}

	constexpr
	T& at(usize row, usize col){
		// Bounds_Check(row < H);
		// Bounds_Check(col < W);
		return data[col][row];
	}

	constexpr
	const T& at(usize row, usize col) const {
		// Bounds_Check(row < H);
		// Bounds_Check(col < W);
		return data[col][row];
	}

	static_assert((W * H * sizeof(T)) < kili(1), "Matrix too big, adjust this assert or use BigMat");
};



template<typename T, usize W, usize H>
constexpr
CMat<T,H,W> transpose(const CMat<T,W,H>& m){
	CMat<T, H, W> t;
	constexpr auto th = t.height();
	constexpr auto tw = t.width();
	for(usize row = 0; row < th; row += 1){
		for(usize col = 0; col < tw; col += 1){
			t.at(row, col) = m.at(col, row);
		}
	}
	return t;
}

template<typename T, usize W, usize H>
constexpr
bool operator==(const CMat<T,W,H>& a, const CMat<T,W,H>& b){
	for(usize i = 0; i < W; i += 1){
		if(a.data[i] != b.data[i]){ return false; }
	}
	return true;
}

template<typename T, usize W, usize H>
constexpr
T sum(const CMat<T,W,H>& m){
	T s{0};
	for(usize i = 0; i < W; i += 1){
		s += sum(m.data[i]);
	}
	return s;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator+(const CMat<T,W,H>& a, const CMat<T,W,H>& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] + b.data[i];
	}
	return m;
}

template<typename T, usize Wa, usize Ha, usize Wb, usize Hb>
constexpr
auto operator*(const CMat<T,Wa,Ha>& a, const CMat<T,Wb,Hb>& b){
	static_assert(Wa == Hb, "Matrix of incompatible sizes for matrix multiplication");
	CMat<T,Wb,Ha> m;
	auto ta = transpose(a);
	constexpr auto resw = Wb;
	constexpr auto resh = Ha;

	for(usize acol = 0; acol < resw; acol += 1){
		for(usize bcol = 0; bcol < resh; bcol += 1){
			m.at(acol, bcol) = sum(ta.col(acol) * b.col(bcol));
		}
	}

	return m;
}


template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator-(const CMat<T,W,H>& a, const CMat<T,W,H>& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] - b.data[i];
	}
	return m;
}


template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator/(const CMat<T,W,H>& a, const CMat<T,W,H>& b){
	// TODO: div by zero
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] / b.data[i];
	}
	return m;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator+(const CMat<T,W,H>& a, const T& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] + b;
	}
	return m;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator-(const CMat<T,W,H>& a, const T& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] - b;
	}
	return m;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator*(const CMat<T,W,H>& a, const T& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] * b;
	}
	return m;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> hadamard_prod(const CMat<T,W,H>& a, const CMat<T,W,H>& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] * b.data[i];
	}
	return m;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator/(const CMat<T,W,H>& a, const T& b){
	CMat<T,W,H> m;
	for(usize i = 0; i < W; i += 1){
		m.data[i] = a.data[i] / b;
	}
	return m;
}

template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator+(const T& a, const CMat<T,W,H>& b){ return b + a; }
template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator-(const T& a, const CMat<T,W,H>& b){ return b - a; }
template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator*(const T& a, const CMat<T,W,H>& b){ return b * a; }
template<typename T, usize W, usize H>
constexpr
CMat<T,W,H> operator/(const T& a, const CMat<T,W,H>& b){ return b / a; }

}

#endif /* Include guard */
