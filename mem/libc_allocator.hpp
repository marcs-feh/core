///
/// Wrapper around libc's malloc and free that conforms to the Allocator
/// interface. Use it *very* sparringly.
///

#ifndef _libc_allocator_hpp_include_
#define _libc_allocator_hpp_include_

#include "mem/allocator.hpp"
#include "mem/mem.hpp"
#include "assert.hpp"

#include <cstdlib>

namespace core{

// TODO: proper impl
struct LibCAllocator {
	void* alloc(usize n){
		void* p = alloc_undef(n);
		mem_set(p, n, 0);
		return p;
	}

	void* alloc_undef(usize n){
		return std::malloc(n);
	}

	void free(void* ptr){
		std::free(ptr);
	}

	void free_all(){
		panic("free_all() not supported");
	}

	bool has_address(void*){
		panic("hasAddress() not supported");
		return false;
	}
};
}


#endif /* Include guard */
