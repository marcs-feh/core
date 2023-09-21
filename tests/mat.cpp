#include "test_urself.hpp"
#include "mat.hpp"

#include "print.hh"

uint test_Mat(){
	using namespace core;
	Test_Begin("Matrix");

	constexpr CMat<int, 4, 3> a = {{
		{9, 0, 0},
		{4, 3, 1},
		{7, 2, 4},
		{4, 5, 0},
	}};

	constexpr CMat<int, 4, 3> b = {{
		{0, 3, 1},
		{5, 6, 2},
		{4, 3, 7},
		{5, 2, 9},
	}};

	constexpr CMat<int, 3, 4> t = {{
		{9, 4, 7, 4},
		{0, 3, 2, 5},
		{0, 1, 4, 0},
	}};

	constexpr auto add = CMat<int, 4, 3>{{
		{9, 3, 1},
		{9, 9, 3},
		{11, 5, 11},
		{9, 7, 9},
	}};
	constexpr auto sub = CMat<int, 4, 3>{{
		{9, -3, -1},
		{-1, -3, -1},
		{3, -1, -3},
		{-1, 3, -9},
	}};
	constexpr auto hadamard = CMat<int, 4, 3>{{
		{0, 0, 0},
		{20, 18, 2},
		{28, 6, 28},
		{20, 10, 0},
	}};
	constexpr auto div = CMat<int, 4, 3>{{
		{9, 0, 0},
		{0, 0, 0},
		{1, 0, 0},
		{0, 1, 0},
	}}; // division by (b+1) to not divide by 0

	constexpr auto mul = CMat<int, 3, 3>{{
		{68, 48,  21}, 
		{80, 34, 18},
		{102, 65, 30},
	}};

	constexpr int sum = 39;

	Tp((a + b) == add);
	Tp((a - b) == sub);
	Tp((a*transpose(b)) == mul);
	Tp(hadamard_prod(a,b) == hadamard);
	Tp((a / (b+1)) == div);

	Tp(transpose(a) == t);
	Tp(transpose(transpose(a)) == a);
	Tp(a.col(0) == (Array<int, 3>{9, 0, 0}));
	Tp(a.row(0) == (Array<int, 4>{9, 4, 7, 4}));
	Tp(core::sum(a) == sum);

	Test_End();
}

