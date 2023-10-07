#include "test_urself.hpp"
#include "defer.hpp"
#include "mem/pool_allocator.hpp"

uint test_PoolAllocator(){
	Test_Begin("Pool Allocator");
	using namespace core;

	constexpr usize n = 250;
	constexpr usize c = 24;

	auto mem = Slice<byte>(new byte[n], n); 
	defer(delete[] mem.raw_ptr());

	auto pool_al = PoolAllocator(mem, c);
	auto al = make_allocator(&pool_al);
	Tp(pool_al._buf != nullptr);
	Tp(pool_al._buf_len <= 250);
	Tp(pool_al._chunk_size == align_forward(c, max_align));

	{
		auto p = make_n<i32>(al, 5);
		defer(destroy(al, p));
		Tp(p.raw_ptr() != nullptr);
	}
	{
		auto p = make_n<i32>(al, 10);
		Tp(p.raw_ptr() == nullptr);
	}
	{
		auto p = make_n<i32>(al, 0);
		Tp(p.raw_ptr() == nullptr);
	}
	{
		auto p = make_n<i32>(al, 10);
		Tp(p.raw_ptr() == nullptr);
	}

	for(usize i = 0, n = pool_al.chunk_count(); i < n; i += 1){
		pool_al.alloc(1);
	}
	Tp(pool_al.alloc(1) == nullptr);

	pool_al.free_all();

	bool ok = true;
	for(usize i = 0, n = pool_al.chunk_count(); i < n; i += 1){
		ok = ok && (pool_al.alloc(1) != nullptr);
	}
	Tp(ok);

	Test_End();
}

