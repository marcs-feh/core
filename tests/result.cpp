#include "result.hpp"
#include "test_urself.hpp"

uint test_Result(){
	Test_Begin("Result");
	using namespace core;

	enum struct Err {None = 0, DivideByZero, TruncationError};

	auto div = [](int a, int b) -> Result<int, Err>{
		if(b == 0){
			return result_err<int, Err>(Err::DivideByZero);
		}
		return result_ok<int, Err>(a/b);
	};

	auto good = div(30, 2);
	auto bad = div(2, 0);

	Tp(good.ok());
	Tp(!bad.ok());

	Tp(bad.error() == Err::DivideByZero);
	Tp(good.get() == 15);

	Tp(bad.get_or(1) == 1);

	good = Err::TruncationError;
	Tp(!good.ok());

	good = int(0);
	Tp(good.ok());
	Tp(good.get_or(1) == 0);

	Test_End();
}
