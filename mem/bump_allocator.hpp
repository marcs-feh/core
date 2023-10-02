///
/// AKA Linear or a non growing Arena allocator, memory is a allocated by
/// "bumping" up an offset, it's the simplest allocator and great for objects of
/// similar lifetime but distinct sizes.
///

#ifndef _bump_allocator_hpp_include_
#define _bump_allocator_hpp_include_

#include "mem/mem.hpp"
#include "mem/allocator.hpp"

namespace core{
struct BumpAllocator {
	uintptr _cap = 0;
	uintptr _offset = 0;
	byte* _data = nullptr;

	void* alloc(usize nbytes){
		void* p = alloc_undef(nbytes);
		if(p != nullptr){
			mem_set(p, nbytes, 0);
		}
		return p;
	}

	void* alloc_undef(usize nbytes){
		if(nbytes == 0){ return nullptr; }
		const auto base = (uintptr)_data;
		uintptr pad = align_forward(base + _offset, core::max_align) - (base + _offset);

		if((_offset + pad + nbytes) >= _cap){
			debug_panic("Out of memory");
			return nullptr;
		}

		void* p = &_data[_offset + pad];

		_offset += pad + nbytes;

		return p;
	}

	bool has_address(void* p){
		auto base = (uintptr)_data;
		auto limit = base + (uintptr)_cap;

		return ptr_in_range(base, (uintptr)p, limit);
	}

	void free(void*){
		panic("free() not supported");
	}

	void free_all(){
		_offset = 0;
	}

	static BumpAllocator make(Slice<byte> buf){
		BumpAllocator b;
		b._cap = buf.len();
		b._data = buf.raw_ptr();
		return b;
	}
};

}


#endif /* Include guard */
