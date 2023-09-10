#include "mem/libc_allocator.hpp"
#include "test_urself.hpp"

uint test_LibCAllocator(){
	Test_Begin("LibCAllocator");
	using namespace core;

	LibCAllocator al;
	{
		int* p = make<int>(al);
		Tp(p != nullptr);
		Tp(*p == 0);
		al.free(p);
	}


	Test_End();
}
