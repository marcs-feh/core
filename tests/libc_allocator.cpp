#include "mem/libc_allocator.hpp"
#include "test_urself.hpp"

uint test_LibCAllocator(){
	Test_Begin("LibC Allocator");
	using namespace core;

	LibCAllocator c;
	auto al = make_allocator(&c);
	{
		int* p = make<int>(al);
		Tp(p != nullptr);
		Tp(*p == 0);
		al.free(p);
	}


	Test_End();
}
