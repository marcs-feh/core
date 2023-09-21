#include "defer.hpp"
#include "test_urself.hpp"
#include "mem/bump_allocator.hpp"

uint test_BumpAllocator(){
	Test_Begin("Bump Allocator");
	{
		constexpr auto n = core::kili(12);

		auto buf = core::Slice(new byte[n], n);
		defer(delete[] buf.raw_ptr());

		auto al = core::BumpAllocator(buf);
		Tp(al._offset == 0);
		int* num = core::make<int>(al);
		Tp(num != nullptr);
		auto nums = core::makeSlice<int>(al, 200);
		Tp(nums.raw_ptr() != nullptr);
		Tp(al.hasAddress(nums.raw_ptr()));
		Tp(!al.hasAddress(nullptr));
		Tp(nums.len() == 200);
		Tp(al._offset > 200);
		{
			bool zeroed = true;
			for(usize i = 0; i < 200; i += 1){
				if(nums[i] != 0){ zeroed = false; }
			}
			Tp(zeroed);
		}
		al.free_all();
		Tp(al._offset == 0);
		Tp(al.alloc(n + 1) == nullptr);
		Tp(al._offset == 0);
	}



	Test_End();
}
