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


int main(){
	// test_Slice();
	// test_View();

	auto v = core::Array<int,4>{3, 1, -2, 4};
	print_arr(v);
	auto a = core::swizzle(v, 0, 1, 0);
	print_arr(a);

	// auto e = core::swizzle(v, 0, 12);
	// print(e.len());

	return 0;
}
