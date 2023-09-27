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
		panic_assert(_has_val, "Attempt to error() from Result(Data) ");
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

	Result(const T& data) : _data(data) {
		_has_val = true;
	}

	Result(T&& data) : _data(move(data)) {
		_has_val = true;
	}

	void operator=(const T& data){
		if(_has_val){
			_data = data;
		} else {
			&_error->~E();
			new (&data) T(data);
		}
	}

	void operator=(T&& data){
		if(_has_val){
			_data = move(data);
		} else {
			&_error->~E();
			new (&data) T(move(data));
		}
	}

	Result(const E& error): _error(error){
		_has_val = false;
	}

	Result(E&& error): _error(move(error)){
		_has_val = false;
	}

	void operator=(const E& error){
		if(_has_val){
			&_data->~E();
			new (&error) T(error);
		} else {
			_error = error;
		}
	}

	void operator=(E&& error){
		if(_has_val){
			&_data->~E();
			new (&error) T(move(error));
		} else {
			_error = move(error);
		}
	}

	static_assert(!typing::same_as<T, E>, "Error and Data type cannot be the same");
};

}


#endif /* Include guard */
