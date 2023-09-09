#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "config.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "slice.hpp"

#ifdef NO_CONCEPTS
#define AllocatorLike typename
#else
#include <concepts>

// Required so the compiler stops crying about it
void* operator new(usize, void*) noexcept;

namespace core {

template<typename AllocType>
concept AllocatorLike = requires(AllocType al, void* rawptr, usize n){
{ al.alloc(n) } -> std::same_as<void*>;
{ al.allocUndef(n) } -> std::same_as<void*>;
{ al.free(rawptr) } -> std::same_as<void>;
{ al.freeAll() } -> std::same_as<void>;
{ al.realloc(rawptr, n) } -> std::same_as<void*>;
};
}

#endif

namespace core{

template<typename T>
T* make(AllocatorLike auto& al){
	T* p = static_cast<T*>(al.alloc(sizeof(T)));
	if(p != nullptr){
		new (p) T;
	}
	return p;
}

template<typename T, typename... CtorArgs>
T* make(AllocatorLike auto& al, CtorArgs ...args){
	T* p = static_cast<T*>(al.alloc(sizeof(T)));
	if(p != nullptr){
		new (p) T(core::forward<CtorArgs...>(args)...);
	}
	return p;
}

template<typename T>
Slice<T> makeSlice(AllocatorLike auto& al, usize n){
	T* p = static_cast<T*>(al.alloc(sizeof(T) * n));

	if(p != nullptr){
		for(usize i = 0; i < n; i += 1){
			new (&p[i]) T;
		}
	}

	return Slice<T>(p, 0);
}


template<typename T, typename... CtorArgs>
Slice<T> makeSlice(AllocatorLike auto& al, usize n, CtorArgs ...args){
	T* p = static_cast<T*>(al.alloc(sizeof(T) * n));

	if(p != nullptr){
		for(usize i = 0; i < n; i += 1){
			new (&p[i]) T(core::forward<CtorArgs...>(args)...);
		}
	}

	return Slice<T>(p, 0);
}

template<typename T>
void destroy(AllocatorLike auto& al, T* ptr){
	// TODO check ownership
	if(ptr != nullptr){
		ptr->~T();
		al.free(ptr);
	}
}

template<typename T>
void destroy(AllocatorLike auto& al, Slice<T> s){
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

#ifdef NO_CONCEPTS
#undef AllocatorLike
#endif

#endif /* Include guard */
