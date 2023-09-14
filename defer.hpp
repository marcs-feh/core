#ifndef _defer_hpp_include_
#define _defer_hpp_include_

#include "utils.hpp"

namespace core {
namespace _defer_impl {
template<typename F>
struct DefferedCall {
	F f;
	DefferedCall(F&& f) : f(forward<F>(f)){}
	~DefferedCall(){ f(); }
};

template<typename F>
auto makeDeferCall(F&& f){
	return DefferedCall<F>(forward<F>(f));
}

template<typename F>
struct DefferedIfCall {
	F f;
	bool cond = false;
	DefferedIfCall(F&& f, bool p) : f(forward<F>(f)), cond(p) {}
	~DefferedIfCall(){ if(cond) { f(); } }
};

template<typename F>
auto makeDeferIfCall(F&& f, bool expr){
	return DefferedIfCall<F>(forward<F>(f), expr);
}

}
}

#define _core_CONCAT_0(X_, Y_) X_##Y_
#define _core_CONCAT_1(X_, Y_) _core_CONCAT_0(X_, Y_)
#define _core_CONCAT_COUNTER(X_) _core_CONCAT_1(X_, __COUNTER__)

#define defer(BLK_) \
	auto _core_CONCAT_COUNTER(_defer_call_) = core::_defer_impl::makeDeferCall([&](){ BLK_; });

#define defer_if(COND_, BLK_) \
	auto _core_CONCAT_COUNTER(_defer_call_) = core::_defer_impl::makeDeferIfCall([&](){ BLK_; }, (COND_) );

#endif /* Include guard */
