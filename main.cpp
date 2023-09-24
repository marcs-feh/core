#include "utils.hpp"
#include "defer.hpp"
#include "assert.hpp"
#include "context.hpp"
#include "dyn_array.hpp"
#include "mem/bump_allocator.hpp"

#include "slice.hpp"
#include "view.hpp"
#include "array.hpp"
#include "mat.hpp"

#include "print.hh"

#include "tests/slice.cpp"
#include "tests/view.cpp"
#include "tests/array.cpp"
#include "tests/mat.cpp"
#include "tests/libc_allocator.cpp"
#include "tests/bump_allocator.cpp"
#include "tests/pool_allocator.cpp"

using namespace core;

int main(){
	uint s =
		+ test_Slice()
		+ test_View()
		+ test_Array()
		+ test_Mat()
		+ test_LibCAllocator()
		+ test_BumpAllocator()
		+ test_PoolAllocator()
	;

	auto al = LibCAllocator();
	auto arr = DynArray<int>(&al);

	print(arr.data.raw_ptr());
	for(usize i = 0; i < 60; i += 1){
		print(arr.append(i * 3), arr.cap());
	}
	print(arr.data.raw_ptr());

	return s;
}
