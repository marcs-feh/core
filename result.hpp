#ifndef _result_hpp_include_
#define _result_hpp_include_

#include "types.hpp"
#include "utils.hpp"
#include "assert.hpp"

namespace core {
template<typename T, typename E>
struct Result {
	union {
		T _data;
		E _error = {0};
	};
	bool _has_val = false;

	constexpr
	bool ok() const { return _has_val; }

	T get() const {
		panic_assert(_has_val, "Attempt to get() from Result(Error) ");
		return _data;
	}

	E error() const {
		panic_assert(!_has_val, "Attempt to error() from Result(Data) ");
		return _error;
	}

	template<typename U>
	T get_or(U&& v) const {
		if(!_has_val){
			return static_cast<T>(forward<U>(v));
		}
		return _data;
	}

	Result(){}

	explicit
	Result(const T& data) : _data(data) {
		_has_val = true;
	}

	explicit
	Result(T&& data) : _data(move(data)) {
		_has_val = true;
	}

	void operator=(const T& val){
		if(_has_val){
			_data = val;
		} else {
			_error.~E();
			new (&_data) T(val);
		}
		_has_val = true;
	}

	void operator=(T&& val){
		if(_has_val){
			_data = move(val);
		} else {
			_error.~E();
			new (&_data) T(move(val));
		}
		_has_val = true;
	}

	explicit
	Result(const E& error): _error(error){
		_has_val = false;
	}

	explicit
	Result(E&& error): _error(move(error)){
		_has_val = false;
	}

	void operator=(const E& error){
		if(_has_val){
		_data.~T();
			new (&error) E(error);
		} else {
			_error = error;
		}
		_has_val = false;
	}

	void operator=(E&& error){
		if(_has_val){
		_data.~T();
			new (&error) E(move(error));
			_has_val = false;
		} else {
			_error = move(error);
		}
		_has_val = false;
	}

	static_assert(!typing::same_as<T, E>, "Error and Data type cannot be the same");
};

template<typename T, typename E>
Result<T,E> result_ok(T&& v){
	return Result<T,E>(forward<T>(v));
}

template<typename T, typename E>
Result<T,E> result_err(E&& e){
	return Result<T,E>(forward<E>(e));
}
}


#endif /* Include guard */
