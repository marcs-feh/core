#include "result.hpp"
#include "test_urself.hpp"
#include "dummy.hpp"

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

	{
		A::reset(); B::reset();
		auto r = Result<A, B>();
		T_All(A::ctor == 0, B::ctor == 1);
		r = A();
		T_All(A::ctor == 1, A::move_ctor == 1, A::move_assign == 0);
		r = A();
		T_All(A::ctor == 2, A::move_ctor == 1, A::move_assign == 1);
		A::reset();
		r = B();
		T_All(A::dtor == 1, B::ctor == 2);
	}

	Test_End();
}
