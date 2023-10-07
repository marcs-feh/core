#ifndef _pool_allocator_hpp_include_
#define _pool_allocator_hpp_include_

#include "slice.hpp"
#include "mem/mem.hpp"
#include "mem/allocator.hpp"

// TODO: extra safety for free()
namespace core{
struct PoolAllocator {
	struct FreeListNode {
		FreeListNode* next = nullptr;
	};
	byte* _buf = nullptr;
	usize _buf_len = 0;
	usize _chunk_size = 0;
	FreeListNode* _head = nullptr;

	usize chunk_count() const {
		return _buf_len / _chunk_size;
	}

	void free_all(){
		usize count = chunk_count();

		for(usize i = 0; i < count; i += 1){
			void* ptr = &_buf[i * _chunk_size];
			auto node = (FreeListNode*)ptr;
			node->next = _head;
			_head = node;
		}
	}

	void free(void *p){
		if (!has_address(p)) {
			debug_assert(p == nullptr,
				"Tried to free non-null pointer that is "
				"not owned by allocator");
			return;
		}

		auto node = (FreeListNode*)p;
		node->next = _head;
		_head = node;
	}

	void* alloc(usize nbytes){
		void* p = alloc_undef(nbytes);
		if(p != nullptr){
			mem_set(p, nbytes, 0);
		}
		return p;
	}

	void* alloc_undef(usize nbytes){
		if(nbytes == 0){ return nullptr; }
		auto node = _head;
		if(node == nullptr){
			debug_panic("Out of memory");
			return nullptr;
		}

		if(nbytes > _chunk_size){
			return nullptr; 
		}

		_head = _head->next;

		return node;
	}

	bool has_address(void *p){
		void* start = _buf;
		void* end = &_buf[_buf_len];
		bool in_range = (p >= start) && (p < end);
		if(!in_range){ return false; }

		usize count = chunk_count();

		for(usize i = 0; i < count; i += 1){
			void* ptr = &_buf[i * _chunk_size];
			if(p == ptr){
				return true;
			}
		}
		return false;
	}

	PoolAllocator(){}

	PoolAllocator(Slice<byte> storage, usize chunk_size, usize chunk_align = max_align) {
		uintptr initial_base = (uintptr)storage.raw_ptr();
		uintptr base         = align_forward(initial_base, chunk_align);

		usize true_length     = storage.len() - (base - initial_base);
		usize true_chunk_size = align_forward(chunk_size, chunk_align);

		Assert(chunk_size >= sizeof(FreeListNode));
		Assert(true_length >= chunk_size);

		_buf        = storage.raw_ptr();
		_buf_len    = true_length;
		_chunk_size = true_chunk_size;
		_head       = nullptr;

		free_all();
	}

};

// constexpr auto pool_alloc_vtbl = allocator_vtable<PoolAllocator>;
//
// Allocator as_allocator(PoolAllocator* al){
// 	return Allocator {
// 		.vtbl = &pool_alloc_vtbl,
// 		.impl = (void*)al,
// 	};
// }

}



#endif /* Include guard */
