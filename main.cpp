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

	auto a = Array<int,4>{0, 9, 2, 4};
	print_arr(a); // [ 0 9 2 4 ]

	auto b = swizzle(a, 3, 2, 0);
	print_arr(b); // [ 4 2 0 ]

	return 0;
}
