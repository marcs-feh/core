#ifndef _optional_hpp_include_
#define _optional_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"

namespace core {
template<typename T>
struct Optional {
	union {
		T _data;
	};
	bool _has_val = false;

	constexpr
	bool ok() const { return _has_val; }

	auto&& destroy(){
		_has_val = false;
		_data.~T();
		return *this;
	}

	T get() const {
		panic_assert(_has_val, "Attempt to get() from Optional(nil)");
		return _data;
	}

	template<typename U>
	T get_or(U&& v) const {
		if(!_has_val){
			return static_cast<T>(forward<U>(v));
		}
		return _data;
	}

	Optional(){}

	Optional(const T& data) : _data(data) {
		_has_val = true;
	}

	Optional(T&& data) : _data(move(data)) {
		_has_val = true;
	}

	void operator=(const T& data){
		if(_has_val){
			_data = data;
		} else {
			new (&data) T(data);
		}
		_has_val = true;
	}

	void operator=(T&& data){
		if(_has_val){
			_data = data;
		} else {
			new (&data) T(move(data));
		}
		_has_val = true;
	}
};

template<typename U>
auto make_optional(U&& v){
	return Optional<U>(forward<U>(v));
}

template<typename U>
auto make_nil(){
	return Optional<U>();
}

}

#endif /* Include guard */