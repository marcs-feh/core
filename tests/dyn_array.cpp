#include "dyn_array.hpp"
#include "test_urself.hpp"
#include "mem/libc_allocator.hpp"

uint test_DynArray(){
	Test_Begin("Dynamic Array");
	using namespace core;
	auto la = LibCAllocator();

	auto ally = make_allocator(&la);
	auto arr = DynArray<int>(ally);
	T_All(
		arr.cap() == DynArray<int>::default_size,
		arr.len() == 0,
		arr._data != nullptr
	);
	Test_End();
}
