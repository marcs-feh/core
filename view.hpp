#ifndef _view_hpp_include_
#define _view_hpp_include_

#include "types.hpp"
#include "slice.hpp"
#include "assert.hpp"

#ifndef NO_BOUNDS_CHECK
#define Bounds_Check(expr_) panic_assert((expr_), "Index out of bounds")
#else
#define Bounds_Check(expr_)
#endif

namespace core {

template<typename T>
struct View {
	const T* _data = nullptr;
	usize _length = 0;

	usize len() const {
		return _length;
	}

	const T* raw_ptr() const {
		return _data;
	}

	const T& operator[](usize idx) const {
		Bounds_Check(idx < _length);
		return _data[idx];
	}

	View<T> view(usize from, usize to) const {
		Bounds_Check((from < _length) && (to < _length));
		if(from >= to){ return View(); }
		usize n = to - from;
		auto s = View<T>(&_data[from], n);
		return s;
	}

	View(){}

	View(const Slice<T>& s): _data{s.raw_ptr()}, _length{s.len()}{}

	View(T* ptr, usize n): _data{ptr}, _length{n} {
		if(_data == nullptr){
			_length = 0;
		}
	}
};

template<typename T>
bool operator==(const View<T>& l, const View<T>& r){
	if(r._length != l._length){ return false; }

	for(usize i = 0; i < l._length; i += 1){
		if(r._data[i] != l._data[i]){ return false; }
	}
	return true;
}

template<typename T>
bool operator==(const View<T>& v, const Slice<T>& s){
	if(s._length != v._length){ return false; }

	for(usize i = 0; i < v._length; i += 1){
		if(s._data[i] != v._data[i]){ return false; }
	}
	return true;
}

template<typename T>
bool operator==(const Slice<T>& s, const View<T>& v){ return v == s; }

}

#undef Bounds_Check

#endif /* Include guard */

