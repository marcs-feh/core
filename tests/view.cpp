#include "view.hpp"
#include "slice.hpp"
#include "types.hpp"
#include "test_urself.hpp"


uint test_View(){
	using namespace core;
	Test_Begin("View");
	{
		View<int> s;
		Tp(s.len() == 0);
		Tp(s.raw_ptr() == nullptr);
	}
	{
		View<int> s (nullptr, 30);
		Tp(s.len() == 0);
		Tp(s.raw_ptr() == nullptr);
	}
	{
		int buf[] = {3, 1, -2, 3, 8, 9, 1, 3, 2};
		View<int> s (buf, 4);
		Tp(s.len() == 4);
		Tp(s.raw_ptr() != nullptr);
		T_All( s[0] == 3, s[1] == 1, s[2] == -2);
	}
	{
		int buf[] = {3, 1, -2, 3, 8, 9, 1, 3, 2};
		Slice<int> s (buf, 4);
		View<int> v = s;
		Tp(v.len() == 4); Tp(v.raw_ptr() == buf);
	}
	{
		int b0[] = {1, 2, 4, 2, 0, 1 };
		int b1[] = {4, 2, 0, 2, 0, 6 };
		auto v0 = View<int>(&b0[2], 3);
		auto s0 = Slice<int>(&b0[2], 3);
		auto v1 = View<int>(&b1[0], 3);
		Tp(v0 == v1);
		Tp(v0 == s0);
	}

	Test_End();
}
