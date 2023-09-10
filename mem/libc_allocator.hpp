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
		void* p = allocUndef(n);
		memSet(p, n, 0);
		return p;
	}

	void* allocUndef(usize n) override {
		return std::malloc(n);
	}

	void free(void* ptr) override {
		std::free(ptr);
	}

	void freeAll() override {
		panic("freeAll() not supportted");
	}

	bool hasAddress(void*) override {
		panic("hasAddress() not supportted");
		return false;
	}
};
}


#endif /* Include guard */
