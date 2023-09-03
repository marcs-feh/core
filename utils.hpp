#ifndef _utils_hpp_include_
#define _utils_hpp_include_

namespace core {
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
