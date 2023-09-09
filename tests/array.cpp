#include "test_urself.hpp"
#include "array.hpp"
#include <cmath>

uint test_Array(){
	using namespace core;
	Test_Begin("Array");

	{
		constexpr Array<f64, 4> a = {-1.0, 0.5, 1.0, -0.3};
		constexpr Array<f64, 4> b = {0.5, 0.25, 0.4, 0.2};

		constexpr Array<f64, 4> add = {a[0]+b[0], a[1]+b[1], a[2]+b[2], a[3]+b[3]};
		constexpr Array<f64, 4> sub = {a[0]-b[0], a[1]-b[1], a[2]-b[2], a[3]-b[3]};
		constexpr Array<f64, 4> mul = {a[0]*b[0], a[1]*b[1], a[2]*b[2], a[3]*b[3]};
		constexpr Array<f64, 4> div = {a[0]/b[0], a[1]/b[1], a[2]/b[2], a[3]/b[3]};

		constexpr f64 summed = a[0] + a[1] + a[2] + a[3];
		const f64 magnitude = std::sqrt(sum(a * a));
		constexpr Array<f64, 4> doubled = {b[0]*2.0, b[1]*2.0, b[2]*2.0, b[3]*2.0};

		Tp((a+b) == add);
		Tp((a-b) == sub);
		Tp((a*b) == mul);
		Tp((a/b) == div);

		Tp(sum(a) == summed);
		Tp(map([](f64 x) -> f64 { return x * 2.0; }, b) == doubled );
		Tp(mag(a) == magnitude);
	}



	Test_End();
}
