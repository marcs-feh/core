///
/// Optional type that can represent a value that *might* be null, using get()
/// on a null value causes a panic. After you get() a value it is moved and the
/// Optional is left in an undefined (but safe to destroy) state.
///

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

	T get(){
		panic_assert(_has_val, "Attempt to get() from Optional(nil)");
		return core::move(_data);
	}

	template<typename U>
	T get_or(U&& v) {
		if(!_has_val){
			return static_cast<T>(forward<U>(v));
		}
		return core::move(_data);
	}

	Optional(){}

	Optional(const T& data) : _data(data) {
		_has_val = true;
	}

	Optional(T&& data) : _data(core::move(data)) {
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
			new (&data) T(core::move(data));
		}
		_has_val = true;
	}

	~Optional(){
		if(_has_val){
			_data.~T();
		}
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
