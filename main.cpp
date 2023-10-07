#include "utils.hpp"

#include "defer.hpp"
#include "assert.hpp"
#include "context.hpp"
#include "dyn_array.hpp"
#include "mem/allocator.hpp"
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
#include "tests/result.cpp"
#include "tests/optional.cpp"
#include "tests/libc_allocator.cpp"
#include "tests/bump_allocator.cpp"
#include "tests/pool_allocator.cpp"
#include "tests/dyn_array.cpp"

using namespace core;

int main(){
	uint s =
		+ test_Slice()
		+ test_View()
		+ test_Array()
		+ test_Mat()
		+ test_Optional()
		+ test_Result()
		+ test_LibCAllocator()
		+ test_BumpAllocator()
		+ test_PoolAllocator()
		+ test_DynArray()
	;

	return s;


}

// TODO: revise structure of result and maybe
