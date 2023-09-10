#include <unistd.h>

#include "utils.hpp"
#include "assert.hpp"
#include "context.hpp"

#include "slice.hpp"
#include "view.hpp"
#include "array.hpp"

#include "print.hh"

#include "tests/slice.cpp"
#include "tests/view.cpp"
#include "tests/array.cpp"
#include "tests/libc_allocator.cpp"

template<typename U>
static void print_arr(U&& v){
	std::cout << "[ ";
	for(usize i = 0; i < v.len(); i += 1){
		std::cout << v[i] << ' ';
	}
	std::cout << "]\n";
}

using namespace core;

int main(){
	test_Slice();
	test_View();
	test_Array();
	test_LibCAllocator();

	return 0;
}
