#include "slice.hpp"
#include "types.hpp"
#include "test_urself.hpp"


uint test_Slice(){
	using namespace core;
	Test_Begin("Slice");
	{
		Slice<int> s;
		Tp(s.len() == 0);
		Tp(s.raw_ptr() == nullptr);
	}
	{
		Slice<int> s (nullptr, 30);
		Tp(s.len() == 0);
		Tp(s.raw_ptr() == nullptr);
	}
	{
		int buf[] = {3, 1, -2, 3, 8, 9, 1, 3, 2};
		Slice<int> s (buf, 4);
		Tp(s.len() == 4);
		Tp(s.raw_ptr() != nullptr);
		T_All( s[0] == 3, s[1] == 1, s[2] == -2);
		s[0] = 69;
		T_All( s[0] == 69, s[1] == 1, s[2] == -2);
	}

	{
		int b0[] = {1, 2, 4, 2, 0, 1 };
		int b1[] = {4, 2, 0, 2, 0, 6 };
		auto s0 = Slice<int>(&b0[2], 3);
		auto s1 = Slice<int>(&b1[0], 3);
		Tp(s0 == s1);

	}

	Test_End();
}
