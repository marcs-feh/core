#include "defer.hpp"
#include "test_urself.hpp"
#include "mem/bump_allocator.hpp"

uint test_BumpAllocator(){
	Test_Begin("Bump Allocator");
	{
		constexpr auto n = core::kili(12);

		auto buf = core::Slice(new byte[n], n);
		defer(delete[] buf.raw_ptr());

		auto bp = core::BumpAllocator(buf);
		auto al = core::make_allocator(&bp);
		Tp(bp._offset == 0);
		int* num = core::make<int>(al);
		Tp(num != nullptr);
		auto nums = core::make_n<int>(al, 200);
		Tp(nums.raw_ptr() != nullptr);
		Tp(al.alloc(0) == nullptr);
		Tp(al.has_address(nums.raw_ptr()));
		Tp(!al.has_address(nullptr));
		Tp(nums.len() == 200);
		Tp(bp._offset > 200);
		{
			bool zeroed = true;
			for(usize i = 0; i < 200; i += 1){
				if(nums[i] != 0){ zeroed = false; }
			}
			Tp(zeroed);
		}
		al.free_all();
		Tp(bp._offset == 0);
		Tp(bp.alloc(n + 1) == nullptr);
		Tp(bp._offset == 0);
	}



	Test_End();
}
