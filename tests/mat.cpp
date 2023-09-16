#include "test_urself.hpp"
#include "mat.hpp"

uint test_Mat(){
	using namespace core;
	Test_Begin("Matrix");

	constexpr Mat<int, 4, 3> a = {
		9, 0, 0,
		4, 3, 1,
		7, 2, 4,
		4, 5, 0,
	};

	constexpr Mat<int, 4, 3> b = {
		0, 3, 1,
		5, 6, 2,
		4, 3, 7,
		5, 2, 9,
	};

	constexpr Mat<int, 3, 4> t = {
		9, 4, 7, 4,
		0, 3, 2, 5,
		0, 1, 4, 0,
	};

	constexpr auto add = Mat<int, 4, 3>{ 9, 3, 1, 9, 9, 3, 11, 5, 11, 9, 7, 9 };
	constexpr auto sub = Mat<int, 4, 3>{ 9, -3, -1, -1, -3, -1, 3, -1, -3, -1, 3, -9 };
	constexpr auto mul = Mat<int, 4, 3>{ 0, 0, 0, 20, 18, 2, 28, 6, 28, 20, 10, 0 };
	constexpr auto div = Mat<int, 4, 3>{ 9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 }; // division by (b+1) to not divide by 0

	Tp((a + b) == add);
	Tp((a - b) == sub);
	Tp((a * b) == mul);
	Tp((a / (b+1)) == div);

	Tp(transpose(a) == t);

	Test_End();
}
