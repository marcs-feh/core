#include "optional.hpp"
#include "test_urself.hpp"

#include <optional>
uint test_Optional(){
	Test_Begin("Optional");
	using namespace core;
	auto div = [](int a, int b) -> Optional<int>{
		if(b == 0){
			return make_nil<int>();
		}
		return make_optional(a / b);
	};

	auto good = div(138, 2);
	auto bad = div(42, 0);

	Tp(good.ok());
	Tp(!bad.ok());

	Tp(good.get() == 69);
	Tp(bad.get_or(69) == 69);

	bad = 100;
	Tp(bad.ok());

	Tp(!good.destroy().ok());
	Tp(good.destroy().get_or(1) == 1);

	good.destroy();
	auto e = make_optional(40).destroy();
	auto f = make_nil<int>().destroy();
	Tp(!e.ok());
	Tp(!f.ok());

	Test_End();
}
