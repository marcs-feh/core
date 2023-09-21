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
		memSet(p, n, 0);
		return p;
	}

	void* alloc_undef(usize n) override {
		return std::malloc(n);
	}

	void free(void* ptr) override {
		std::free(ptr);
	}

	void free_all() override {
		panic("free_all() not supportted");
	}

	bool hasAddress(void*) override {
		panic("hasAddress() not supportted");
		return false;
	}
};
}


#endif /* Include guard */
