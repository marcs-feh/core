#ifndef _mat_hpp_include_
#define _mat_hpp_include_

#include "types.hpp"
#include "array.hpp"

namespace core {
template<typename T, usize N, usize M>
struct Mat {
	using Row = Array<T, M>;
	using Col = Array<T, N>;

	Row data[N];

	constexpr
	Row row(usize idx){
		return data[idx];
	}

	constexpr
	Col col(usize idx){
		Col c;
		for(usize i = 0; i < N; i += 1){
			c[i] = data[i][idx];
		}
		return c;
	}

	constexpr
	T& at(usize row, usize col){
		return (data[row])[col];
	}

	constexpr
	const T& at(usize row, usize col) const {
		return (data[row])[col];
	}

};

}



#endif /* Include guard */
