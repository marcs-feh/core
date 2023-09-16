#include <unistd.h>

#include "utils.hpp"
#include "defer.hpp"
#include "assert.hpp"
#include "context.hpp"
#include "mem/bump_allocator.hpp"

#include "slice.hpp"
#include "view.hpp"
#include "array.hpp"
#include "mat.hpp"

#include "print.hh"

#include "tests/slice.cpp"
#include "tests/view.cpp"
#include "tests/array.cpp"
#include "tests/libc_allocator.cpp"
#include "tests/bump_allocator.cpp"

using namespace core;

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


int main(){
	test_Slice();
	test_View();
	test_Array();
	test_LibCAllocator();
	test_BumpAllocator();

	auto mat = Mat<int, 2, 3>{
		1,2,3,
		4,5,6,
	};

	print_mat(mat);
	print_mat(transpose(mat));
	print_mat(transpose( transpose(mat) ));


	return 0;
}
