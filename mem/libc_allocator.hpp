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
struct LibCAllocator : public Allocator {
	void* alloc(usize n) override {
		void* p = alloc_undef(n);
		mem_set(p, n, 0);
		return p;
	}

	void* alloc_undef(usize n) override {
		return std::malloc(n);
	}

	void free(void* ptr) override {
		std::free(ptr);
	}

	void free_all() override {
		panic("free_all() not supported");
	}

	bool hasAddress(void*) override {
		panic("hasAddress() not supported");
		return false;
	}
};
}


#endif /* Include guard */
