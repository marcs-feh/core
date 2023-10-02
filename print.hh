#ifndef _print_hh_include_
#define _print_hh_include_

#include <iostream>
#include <utility>

#include "types.hpp"
#include "mat.hpp"
#include "array.hpp"

namespace {

template<typename U>
static void print_arr(U&& v){
	std::cout << "[ ";
	for(usize i = 0; i < v.len(); i += 1){
		std::cout << v[i] << ' ';
	}
	std::cout << "]";
}

template<typename U>
static void print_mat(U&& m){
	std::cout << "[ ";
	for(usize i = 0; i < m.height(); i += 1){
		for(usize j = 0; j < m.width(); j += 1){
			std::cout << m.at(i, j) << ' ';
		}
		if((i + 1) != m.height()){
			std::cout << "| ";
		}
	}
	std::cout << "]";
}

template<typename T>
void print_rec(const T& x){
	std::cout << x;
}

template<typename T, usize W, usize H>
void print_rec(const core::CMat<T, W, H>& x){
	print_mat(x);
}

template<typename T, usize N>
void print_rec(const core::Array<T,N>& x){
	print_arr(x);
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
