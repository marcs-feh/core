///
/// Result is a tagged union between an error and a desired type, mainly meant
/// to be used as an alternative to exceptions. After you get() or error() a
/// value, it is moved out of the Result and left in an undefined (but safe to
/// destroy) state.
///

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
		E _error;
	};
	bool _is_error = false;

	constexpr
	bool ok() const { return _is_error; }

	T get(){
		panic_assert(_is_error, "Attempt to get() from Result(Error) ");
		return core::move(_data);
	}

	E error(){
		panic_assert(!_is_error, "Attempt to error() from Result(Data) ");
		return core::move(_error);
	}

	template<typename U>
	T get_or(U&& v) const {
		if(!_is_error){
			return static_cast<T>(forward<U>(v));
		}
		return move(_data);
	}

	Result() : _error() {}

	explicit
	Result(const T& data) : _data(data) {
		_is_error = true;
	}

	explicit
	Result(T&& data) : _data(core::move(data)) {
		_is_error = true;
	}

	void operator=(const T& val){
		if(_is_error){
			_data = val;
		} else {
			_error.~E();
			new (&_data) T(val);
		}
		_is_error = true;
	}

	void operator=(T&& val){
		if(_is_error){
			_data = core::move(val);
		} else {
			_error.~E();
			new (&_data) T(core::move(val));
		}
		_is_error = true;
	}

	explicit
	Result(const E& error): _error(error){
		_is_error = false;
	}

	explicit
	Result(E&& error): _error(core::move(error)){
		_is_error = false;
	}

	void operator=(const E& error){
		if(_is_error){
		_data.~T();
			new (&error) E(error);
		} else {
			_error = error;
		}
		_is_error = false;
	}

	void operator=(E&& error){
		if(_is_error){
		_data.~T();
			new (&error) E(core::move(error));
			_is_error = false;
		} else {
			_error = core::move(error);
		}
		_is_error = false;
	}

	~Result(){
		if(_is_error){
			_data.~T();
		} else {
			_error.~E();
		}
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
