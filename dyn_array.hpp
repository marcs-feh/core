#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "mem/allocator.hpp"
#include "slice.hpp"

#include <optional>

namespace core {
template<typename T>
struct DynArray {
	Allocator* alloc = nullptr;
	usize length = 0;
	Slice<T> data = Slice<T>();

	constexpr
	usize len() const {
		return length;
	}

	constexpr
	usize cap() const {
		return data.len();
	}

	template<typename U>
	usize append(U&& e){
		if((length + 1) >= cap()){
			bool ok = _expand_cap(increase_cap(cap()));
			if(!ok){
				debug_panic("Could not append element");
				return length;
			}
		}

		T* p = data.raw_ptr();
		new (&p[length]) T(static_cast<T>(forward<U>(e)));
		length += 1;
		return length;
	}

	// TODO: realloc()
	bool _expand_cap(usize new_size){
		// panic_assert(new_size > cap(), "Cannot _expand_cap() to a smaller capacity");
		T* new_data = static_cast<T*>(alloc->alloc(new_size * sizeof(T)));

		if(new_data == nullptr){
			return false;
		}

		T* old_data = data.raw_ptr();

		for(usize i = 0; i < length; i += 1){
			new (&new_data[i]) T(move(old_data[i]));
		}

		destroy(*alloc, data);

		data = Slice<T>(new_data, new_size);
		return true;
	}

	DynArray(){}

	DynArray(Allocator* al) {
		alloc = al;
		Assert(alloc != nullptr);

		T* data_ptr = static_cast<T*>(alloc->alloc(default_size * sizeof(T)));
		Assert(data_ptr != nullptr);
		data = Slice<T>(data_ptr, default_size);

	}

	~DynArray(){
		destroy(*alloc, data);
	}

	static constexpr usize min_size = 4;
	static constexpr usize default_size = 5;
	static constexpr auto increase_cap = [](usize n) {
		usize x = (n * 1.5) + 1;
		return align_forward(x, max_align);
	};
};
}


#endif /* Include guard */
