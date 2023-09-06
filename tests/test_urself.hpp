#ifndef _test_urself_hpp_include_
#define _test_urself_hpp_include_

#include <cstdio>


namespace tu {

using uint = unsigned int;
using TestProc = uint (*)(void);

#ifndef TEST_URSELF_COLORLESS
constexpr auto COL_FAIL  = "\e[0;31m";
constexpr auto COL_PASS  = "\e[0;32m";
constexpr auto COL_TITLE = "\e[1;37m";
constexpr auto COL_RESET = "\e[0m";
#else
constexpr auto COL_FAIL  = "";
constexpr auto COL_PASS  = "";
constexpr auto COL_TITLE = "";
constexpr auto COL_RESET = "";
#endif

struct Test {
	const char* title;
	uint tests_count;
	uint error_count;

	void displayHeader(){
		printf("[%s%s%s]\n", COL_TITLE, title, COL_RESET );
	}

	void assertExp(bool expr, const char* msg){
		tests_count += 1;
		if(!expr){
			error_count += 1;
			printf("  Failed: %s\n", msg);
		}
	}

	void displayResults(){
		if(error_count > 0){
			printf("%sFAIL%s", COL_FAIL, COL_RESET);
		} else {
			printf("%sPASS%s", COL_PASS, COL_RESET);
		}
		printf(" ok in %u/%u\n", tests_count - error_count, tests_count);
	}
};
template<typename T>
bool ensureAll(T&& v){
	return bool(v);
}

template<typename T, typename... Args>
bool ensureAll(T&& v, Args&& ...args){
	return bool(v) && ensureAll(args...);
}

template<typename T>
bool ensureAny(T&& v){
	return bool(v);
}

template<typename T, typename... Args>
bool ensureAny(T&& v, Args&& ...args){
	return bool(v) || ensureAny(args...);
}


}

#define Test_Begin(title_) \
	using tu::Test; \
	auto _test_ = (Test){ .title = title_, .tests_count = 0, .error_count = 0}; \
	_test_.displayHeader();

#define Test_End() \
	_test_.displayResults(); \
	return _test_.error_count;

#define Test_Log(fmt, ...) printf("  >> " fmt "\n", __VA_ARGS__);

#define Tp(expr_) { _test_.assertExp( (expr_), #expr_ ); }

#define T_All(...) { _test_.assertExp(tu::ensureAll(__VA_ARGS__), "All[ " #__VA_ARGS__  " ]"); }

#define T_None(...) { _test_.assertExp(!tu::ensureAll(__VA_ARGS__), "All[ " #__VA_ARGS__  " ]"); }

#define T_Any(...) { _test_.assertExp(tu::ensureAny(__VA_ARGS__), "Any[ " #__VA_ARGS__  " ]");}


#endif /* Include guard */
