#ifndef _libc_allocator_hpp_include_
#define _libc_allocator_hpp_include_

#include "mem/allocator.hpp"
#include "mem/mem.hpp"
#include "assert.hpp"

#include <cstdlib>

namespace core{
struct LibCAllocator {

	void* alloc(usize n){
		void* p = allocUndef(n);
		memSet(p, n, 0);
		return p;
	}

	void* allocUndef(usize n){
		return std::malloc(n);
	}

	void free(void* ptr){
		std::free(ptr);
	}

	void freeAll(){
		panic("freeAll not supportted");
	}

};
}


#endif /* Include guard */
