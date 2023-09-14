#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "config.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "slice.hpp"
#include "view.hpp"
#include "mem/mem.hpp"

#ifndef NO_CONCEPTS
#include <concepts>

// Required so the compiler stops crying about it
void* operator new(usize, void*) noexcept;

namespace core {


struct Allocator {
	virtual void* alloc(usize nbytes) = 0;
	virtual void* allocUndef(usize nbytes) = 0;
	virtual bool hasAddress(void* p) = 0;
	virtual void free(void* p) = 0;
	virtual void freeAll() = 0;
	// void* realloc(void* p, usize old_size, usize new_size);
};

template<typename T>
T* make(Allocator& al){
	T* p = static_cast<T*>(al.alloc(sizeof(T)));
	if(p != nullptr){
		new (p) T;
	}
	return p;
}

template<typename T, typename... CtorArgs>
T* make(Allocator& al, CtorArgs&& ...args){
	T* p = static_cast<T*>(al.alloc(sizeof(T)));
	if(p != nullptr){
		new (p) T(core::forward<CtorArgs...>(args)...);
	}
	return p;
}

template<typename T>
Slice<T> makeSlice(Allocator& al, usize n){
	T* p = static_cast<T*>(al.alloc(sizeof(T) * n));

	if(p != nullptr){
		for(usize i = 0; i < n; i += 1){
			new (&p[i]) T;
		}
	}

	return Slice<T>(p, n);
}

template<typename T>
View<T> makeView(Allocator& al, usize n){
	auto s = makeSlice<T>(al, n);
	return View(s);
}

template<typename T, typename... CtorArgs>
Slice<T> makeSlice(Allocator& al, usize n, CtorArgs&& ...args){
	T* p = static_cast<T*>(al.alloc(sizeof(T) * n));

	if(p != nullptr){
		for(usize i = 0; i < n; i += 1){
			new (&p[i]) T(core::forward<CtorArgs...>(args)...);
		}
	}

	return Slice<T>(p, 0);
}

template<typename T, typename... CtorArgs>
View<T> makeView(Allocator& al, usize n, CtorArgs&& ...args){
	auto s = makeSlice<T>(al, n, core::forward<CtorArgs...>(args)...);
	return View(s);
}


template<typename T>
void destroy(Allocator& al, T* ptr){
	// TODO check ownership
	if(ptr != nullptr){
		ptr->~T();
		al.free(ptr);
	}
}

template<typename T>
void destroy(Allocator& al, View<T> s){
	// TODO check ownership
	T* ptr = s.raw_ptr();
	usize n = s.len();
	if(ptr != nullptr){
		for(usize i = 0; i < n; i += 1){
			(&ptr[i])->~T();
		}
		al.free(ptr);
	}
}

}
#endif /* NO_CONCEPTS */

#ifdef NO_CONCEPTS
#undef Allocator
#endif

#endif /* Include guard */
