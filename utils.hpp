#ifndef _utils_hpp_include_
#define _utils_hpp_include_

#include "config.hpp"

namespace core {

namespace typing {

template<typename T>
struct RemoveReferenceType {typedef T Type; };
template<typename T>
struct RemoveReferenceType<T&> {typedef T Type; };
template<typename T>
struct RemoveReferenceType<T&&> {typedef T Type; };

template<typename T, T v>
struct IntegralConstant {
	static constexpr T value = v;
	typedef T ValueType;
	constexpr operator ValueType() { return value; }
};

using True_Type  = IntegralConstant<bool, true>;
using False_Type = IntegralConstant<bool, false>;

template<typename T>
struct IsLValueReference : False_Type {};
template<typename T>
struct IsLValueReference<T&> : True_Type {};
template<typename T>
struct IsLValueReference<T&&> : False_Type {};

template<typename T>
struct IsRValueReference : False_Type {};
template<typename T>
struct IsRValueReference<T&> : False_Type {};
template<typename T>
struct IsRValueReference<T&&> : True_Type {};

}

template<typename T>
using RemoveReference = typename typing::RemoveReferenceType<T>::Type;

template<typename T>
constexpr bool is_lvalue_ref = typing::IsLValueReference<T>::value;

template<typename T>
constexpr bool is_rvalue_ref = typing::IsRValueReference<T>::value;

// Cast x to rvalue reference
template<typename T>
constexpr RemoveReference<T>&& move(T&& x){
	typedef RemoveReference<T>&& Rv;
	return static_cast<Rv>(x);
}

// Contitionally moves x, if and only if, x is an rvalue reference. Requires
// passing template type explicitly. This is used to implement "perfect forwarding"
template<typename T>
constexpr T&& forward(RemoveReference<T>& x){
	return static_cast<T&&>(x);
}

// Contitionally moves x, if and only if, x is an rvalue reference. Requires
// passing template type explicitly. This is used to implement "perfect forwarding"
template<typename T>
constexpr T&& forward(RemoveReference<T>&& x){
	static_assert(!is_lvalue_ref<T>, "Cannot use forward() to convert an rvalue to an lvalue");
	return static_cast<T&&>(x);
}

// Swap values of a and b
template<typename T>
constexpr
void swap(T& a, T& b){
	T t = move(b);
	b   = move(a);
	a   = move(t);
}

// Replaces x with val and returns the old value of x
template<typename T, typename U = T>
T exchange(T& x, U&& val){
	T t = move(x);
	x   = forward<U>(val);
	return t;
}

template<typename T>
T min(const T& a, const T& b){
	if(a < b){ return a; }
	return b;
}

template<typename T, typename ...Rest>
T min(const T& a, const T& b, const Rest& ...rest){
	if(a < b){
		return min(a, rest...);
	}
	else {
		return min(b, rest...);
	}
}

template<typename T>
T max(const T& a, const T& b){
	if(a > b){ return a; }
	return b;
}

template<typename T, typename ...Rest>
T max(const T& a, const T& b, const Rest& ...rest){
	if(a > b){
		return max(a, rest...);
	}
	else {
		return max(b, rest...);
	}
}

template<typename T>
T clamp(const T& a, const T& x, const T& b){
	if(x < a){ return a; }
	if(x > b){ return b; }
	return x;
}

template<typename A, typename B = A>
struct Pair {
	A a;
	B b;
};
}

#endif /* Include guard */
