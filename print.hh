#ifndef _print_hh_include_
#define _print_hh_include_

#include <iostream>
#include <utility>

#include "types.hpp"

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

template<typename U>
static void print_arr(U&& v){
	std::cout << "[ ";
	for(usize i = 0; i < v.len(); i += 1){
		std::cout << v[i] << ' ';
	}
	std::cout << "]\n";
}

template<typename U>
static void print_mat(U&& m){
	for(usize i = 0; i < m.height(); i += 1){
		auto r = m.row(i);

		std::cout << "| ";
		for(usize i = 0; i < r.len(); i += 1){
			std::cout << r[i] << ' ';
		}
		std::cout << "|\n";
	}
}



}

template<typename ...Args>
void print(const Args&... args){
	print_rec(args...);
	std::cout << '\n';
}

#endif /* Include guard */
