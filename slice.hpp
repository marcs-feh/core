#ifndef _slice_hpp_include_
#define _slice_hpp_include_

#include "types.hpp"

#ifndef NO_BOUNDS_CHECK
#include "assert.hpp"
#define Bounds_Check(expr_) panic_assert((expr_), "Index out of bounds")
#else
#define Bounds_Check(expr_)
#endif

namespace core {

template<typename T>
struct Slice {
	T* _data = nullptr;
	usize _length = 0;

	usize len() const {
		return _length;
	}

	T* raw_ptr() const {
		return _data;
	}

	T& operator[](usize idx) const {
		Bounds_Check(idx < _length);
		return _data[idx];
	}

	Slice<T> slice(usize from, usize to) const {
		Bounds_Check((from < _length) && (to < _length));
		if(from >= to){ return Slice(); }
		usize n = to - from;
		auto s = Slice<T>(&_data[from], n);
		return s;
	}


	Slice(){}

	Slice(T* ptr, usize n): _data{ptr}, _length{n} {
		if(_data == nullptr){
			_length = 0;
		}
	}
};

template<typename T>
bool operator==(const Slice<T>& l, const Slice<T>& r){
	if(r._length != l._length){ return false; }

	for(usize i = 0; i < l._length; i += 1){
		if(r._data[i] != l._data[i]){ return false; }
	}
	return true;
}

}

#undef Bounds_Check

#endif /* Include guard */
