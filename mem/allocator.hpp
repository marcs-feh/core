///
/// Allocator interface and utilities, this is completely different from the
/// usual std::allocator trash. Allocators are not responsible for running
/// destructors or constructors, they *only* allocate/deallocate memory. You can
/// query which functions an allocator supports at runtime. A failed allocation
/// returns nullptr.
///

#ifndef _allocator_hpp_include_
#define _allocator_hpp_include_

#include "config.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "slice.hpp"
#include "view.hpp"
#include "mem/mem.hpp"

// Required so the compiler stops crying about it
void* operator new(usize, void*) noexcept;

namespace core {

#include "internal/allocator_interface.hpp"

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
Slice<T> make_n(Allocator& al, usize n){
	T* p = static_cast<T*>(al.alloc(sizeof(T) * n));

	if(p != nullptr){
		for(usize i = 0; i < n; i += 1){
			new (&p[i]) T;
		}
	}

	return Slice<T>(p, n);
}

template<typename T, typename... CtorArgs>
Slice<T> make_n(Allocator& al, usize n, CtorArgs&& ...args){
	T* p = static_cast<T*>(al.alloc(sizeof(T) * n));

	if(p != nullptr){
		for(usize i = 0; i < n; i += 1){
			new (&p[i]) T(core::forward<CtorArgs...>(args)...);
		}
	}

	return Slice<T>(p, 0);
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
void destroy(Allocator& al, Slice<T> s){
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

#endif /* Include guard */

// struct Allocator {
// 	struct VTable {
// 		using Alloc       = void* (*)(void* impl, usize nbytes);
// 		using AllocUnsafe = void* (*)(void* impl, usize nbytes);
// 		using Free        = void (*)(void* impl, void* p);
// 		using FreeAll     = void (*)(void* impl);
// 		using HasAddress  = bool (*)(void* impl, void* p);
//
// 		Alloc alloc;
// 		Alloc alloc_undef;
// 		Free free;
// 		FreeAll free_all;
// 		HasAddress has_address;
// 	};
// 	const VTable* const vtbl;
// 	void* const impl;
//
// 	// SYNTAX SUGAR BELOW
// 	void* alloc(usize nbytes){ return vtbl->alloc(impl, nbytes); }
// 	void* alloc_undef(usize nbytes){ return vtbl->alloc_undef(impl, nbytes); }
// 	void free(void* p){ return vtbl->free(impl, p); }
// 	void free_all(){ return vtbl->free_all(impl); }
// 	bool has_address(void* p){ return vtbl->has_address(impl, p); }
// };
//
// template<typename T>
// constexpr Allocator::VTable allocator_vtable = {
// 	.alloc = [](void* impl, usize n) -> void*{
// 		auto al = reinterpret_cast<T*>(impl);
// 		return al->alloc(n);
// 	},
// 	.alloc_undef = [](void* impl, usize n) -> void* {
// 		auto al = reinterpret_cast<T*>(impl);
// 		return al->alloc_undef(n);
// 	},
// 	.free = [](void* impl, void* p) -> void {
// 		auto al = reinterpret_cast<T*>(impl);
// 		return al->free(p);
// 	},
// 	.free_all = [](void* impl) -> void {
// 		auto al = reinterpret_cast<T*>(impl);
// 		return al->free_all();
// 	},
// 	.has_address = [](void* impl, void* p) -> bool {
// 		auto al = reinterpret_cast<T*>(impl);
// 		return al->has_address( p);
// 	},
// };
//
// template<typename Impl>
// auto as_allocator(Impl* impl){
// 	constexpr auto vtbl = &allocator_vtable<Impl>;
// 	return Allocator{
// 		.vtbl = vtbl,
// 		.impl = (void*)impl,
// 	};
// }

