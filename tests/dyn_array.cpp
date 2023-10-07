#include "dyn_array.hpp"
#include "test_urself.hpp"
#include "mem/libc_allocator.hpp"

#include "print.hh"

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

	Tp(arr.append(4) == 1);
	Tp(arr.append(2) == 2);
	Tp(arr.append(0) == 3);

	{
		auto b = DynArray<int>(ally);
		b.append(4);
		b.append(2);
		b.append(0);
		Tp(arr == b);
		b.pop();
		Tp(b.len() == 2);
		Tp(arr != b);
	}

	{
		auto b = DynArray<int>(ally);
		b.append(6); b.append(9); b.append(4); b.append(2); b.append(0);
		Tp(arr.insert(0, 6) == 4);
		Tp(arr.insert(1, 9) == 5);
		Tp(arr == b)
	}


	Test_End();
}
