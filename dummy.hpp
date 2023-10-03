#ifndef _dummy_cpp_include_
#define _dummy_cpp_include_

#define DUMMY(name_)                                  \
struct name_ {                                        \
	static int ctor;                                  \
	static int copy_ctor;                             \
	static int copy_assign;                           \
	static int move_ctor;                             \
	static int move_assign;                           \
	static int dtor;                                  \
                                                      \
	name_(){ ctor += 1; }                             \
	name_(name_ const&){ copy_ctor += 1; }            \
	void operator=(name_ const&){ copy_assign += 1; } \
	void operator=(name_&&){ move_assign += 1; }      \
	name_(name_ &&){ move_ctor += 1; }                \
	~name_(){ dtor += 1; }                            \
                                                      \
	static void reset(){                              \
		name_::ctor        = 0;                       \
		name_::copy_ctor   = 0;                       \
		name_::copy_assign = 0;                       \
		name_::move_ctor   = 0;                       \
		name_::move_assign = 0;                       \
		name_::dtor        = 0;                       \
	}                                                 \
	int val;                                          \
};                                                    \
inline int name_::ctor        = 0;                    \
inline int name_::copy_ctor   = 0;                    \
inline int name_::copy_assign = 0;                    \
inline int name_::move_ctor   = 0;                    \
inline int name_::move_assign = 0;                    \
inline int name_::dtor        = 0;                    \

DUMMY(A);
DUMMY(B);

#endif /* Include guard */
