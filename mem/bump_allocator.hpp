#ifndef _bump_allocator_hpp_include_
#define _bump_allocator_hpp_include_

#include "mem/mem.hpp"
#include "mem/allocator.hpp"

namespace core{
struct BumpAllocator : Allocator {
	uintptr _cap = 0;
	uintptr _offset = 0;
	byte* _data = nullptr;

	void* alloc(usize nbytes) override {
		void* p = allocUndef(nbytes);
		if(p != nullptr){
			memSet(p, nbytes, 0);
		}
		return p;
	}

	void* allocUndef(usize nbytes) override {
		const auto base = (uintptr)_data;
		uintptr pad = alignForward(base + _offset, core::max_align) - (base + _offset);

		if((_offset + pad + nbytes) >= _cap){
			// Out of memory
			return nullptr;
		}

		void* p = &_data[_offset + pad];

		_offset += pad + nbytes;

		return p;
	}

	bool hasAddress(void* p) override {
		auto base = (uintptr)_data;
		auto limit = base + (uintptr)_cap;

		return ptrInRange(base, (uintptr)p, limit);
	}

	void free(void*) override {
		panic("free() not supported");
	}

	void freeAll() override {
		_offset = 0;
	}

	BumpAllocator(){}
	BumpAllocator(byte* buf, usize n) : _cap{n}, _data{buf} {}
	BumpAllocator(Slice<byte> buf) : _cap{buf.len()}, _data{buf.raw_ptr()}{}
};
}


#endif /* Include guard */
