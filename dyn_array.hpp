#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "mem/allocator.hpp"
#include "result.hpp"
#include "slice.hpp"

namespace core {

template<typename T>
struct DynArray {
	Allocator _alloc = {0,0};
	usize _length = 0;
	Slice<T> _data = Slice<T>();

	constexpr
	usize len() const {
		return _length;
	}

	constexpr
	usize cap() const {
		return _data.len();
	}

	template<typename U>
	usize append(U&& e){
		if((_length + 1) >= cap()){
			bool ok = _expand_cap(increase_cap(cap()));
			if(!ok){
				debug_panic("Could not append element");
				return _length;
			}
		}

		T* p = _data.raw_ptr();
		new (&p[_length]) T(static_cast<T>(forward<U>(e)));
		_length += 1;
		return _length;
	}

	// TODO: realloc()
	bool _expand_cap(usize new_size){
		// panic_assert(new_size > cap(), "Cannot _expand_cap() to a smaller capacity");
		T* new_data = static_cast<T*>(_alloc.alloc(new_size * sizeof(T)));

		if(new_data == nullptr){
			return false;
		}

		T* old_data = _data.raw_ptr();

		for(usize i = 0; i < _length; i += 1){
			new (&new_data[i]) T(core::move(old_data[i]));
		}

		destroy(_alloc, _data);

		_data = Slice<T>(new_data, new_size);
		return true;
	}

	DynArray(){}

	DynArray(Allocator al) {
		_alloc = al;

		T* data_ptr = static_cast<T*>(_alloc.alloc(DynArray<T>::default_size * sizeof(T)));

		Assert(data_ptr != nullptr);
		// *this = DynArray();
		_data = Slice<T>(data_ptr, DynArray<T>::default_size);
	}

	// TODO: allow shallow copies?
	DynArray(DynArray const&) = delete;
	void operator=(DynArray const&) = delete;

	DynArray(DynArray&& a){
		_data = core::exchange(a._data, Slice<T>());
		_alloc = core::exchange(a._alloc, Allocator());
		_length = core::exchange(a._length, 0);
	}

	void operator=(DynArray&& a){
		destroy(_alloc, _data);
		_data = core::exchange(a._data, Slice<T>());
		_alloc = core::exchange(a._alloc, Allocator());
		_length = core::exchange(a._length, 0);
	}

	~DynArray(){
		destroy(_alloc, _data);
	}

	static constexpr usize min_size = 4;
	static constexpr usize default_size = 5;
	static constexpr auto increase_cap = [](usize n) {
		usize x = (n * 1.5) + 1;
		return align_forward(x, max_align);
	};
};

// TODO: use actual error type
// template<typename T>
// Result<DynArray<T>, int> make_dyn_array(Allocator al) {
// 	DynArray<T> arr;
// 	arr.alloc = al;
// 	// Assert(bool(arr.alloc));
//
// 	T* data_ptr = static_cast<T*>(arr.alloc.alloc(DynArray<T>::default_size * sizeof(T)));
// 	Assert(data_ptr != nullptr);
// 	arr.data = Slice<T>(data_ptr, DynArray<T>::default_size);
//
// 	return result_ok<DynArray<T>, int>(core::move(arr));
// }
}


#endif /* Include guard */
