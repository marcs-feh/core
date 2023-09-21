#ifndef _pool_allocator_hpp_include_
#define _pool_allocator_hpp_include_

#include "slice.hpp"
#include "mem/mem.hpp"
#include "mem/allocator.hpp"

namespace core{

struct FreeListNode {
	byte* next = nullptr;
};

struct PoolAllocator : public Allocator {
	byte* _buf;
	usize _buf_len;
	usize _chunk_size;
	FreeListNode* _head;

	PoolAllocator() : _buf{nullptr}, _buf_len{0}, _chunk_size{0}, _head{nullptr} {}

	PoolAllocator(Slice<byte> storage, usize chunk_size, usize chunk_align = max_align) {
		uintptr original_start = (uintptr)storage.raw_ptr();
		uintptr start = align_forward(original_start, chunk_align);
		usize true_length = storage.len() - (start - original_start);
		usize true_chunk_size = align_forward(chunk_size, chunk_align);

		Assert(chunk_size >= sizeof(FreeListNode));
		Assert(true_length >= chunk_size);

		_buf = storage.raw_ptr();
		_buf_len = true_length;
		_chunk_size = true_chunk_size;
		_head = nullptr;

		free_all();
	}

	void free_all() override {}

	void free(void *p) override {}

	void * alloc(usize nbytes) override {}

	void * alloc_undef(usize nbytes) override{}
};

}



#endif /* Include guard */
