#ifndef _print_hh_include_
#define _print_hh_include_

#include <iostream>
#include <utility>

namespace {
	template<typename T>
	void print_rec(const T& x){
		std::cout << x;
	}

	template<typename T, typename ...Args>
	void print_rec(const T& x, const Args&... args){
		print_rec(x);
		std::cout << ' ';
		print_rec(args...);
	}
}

template<typename ...Args>
void print(const Args&... args){
	print_rec(args...);
	std::cout << '\n';
}

#endif /* Include guard */
