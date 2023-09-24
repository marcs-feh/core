///
/// Assert and panic macros
///

#ifndef _assert_hpp_include_
#define _assert_hpp_include_

// TODO: support recovery routines
// TODO: different naming conv for macros?

#include <cstdio>
#include <cstdlib> /* abort() */

#include "config.hpp"

#define Abort_Program() \
	{ std::abort(); }

#define Assert(expr_) core::debug_assert((expr_), #expr_)

namespace core {
static inline
void panic(const char* msg = nullptr){
	if(msg != nullptr){
		fprintf(stderr, "Panic: %s\n", msg);
	}
	Abort_Program();
}

static inline 
void panic_assert(bool expr, const char* msg){
	if(!expr){
		fprintf(stderr, "Panic: %s\n", msg);
		Abort_Program();
	}
}


#ifndef NO_DEBUG_ASSERT
static inline
void debug_assert(bool expr, const char* msg){
	if(!expr){
		fprintf(stderr, "Failed assert: %s\n", msg);
		Abort_Program();
	}
}

static inline
void debug_panic(const char* msg = nullptr){
	if(msg != nullptr){
		fprintf(stderr, "Panic: %s\n", msg);
	}
	Abort_Program();
}
#else
static inline
void debug_assert(bool, const char*){}
static inline
void debug_panic(const char* = nullptr){}
#endif

}

#endif /* Include guard */
