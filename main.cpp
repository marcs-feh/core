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


int main(){
	test_Slice();
	test_View();
	test_Array();
	test_LibCAllocator();
	test_BumpAllocator();

	Mat<int, 3, 2> mat = {
		1,2,3,4,5,6
	};


	print_arr(mat.row(0));
	print_arr(mat.row(1));
	print_arr(mat.row(2));

	print_arr(mat.col(0));
	print_arr(mat.col(1));

	return 0;
}
