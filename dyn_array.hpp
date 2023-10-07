///
/// A Dynamic Array is a growable linear collection of elements of type T.
///

#ifndef _dyn_array_hpp_include_
#define _dyn_array_hpp_include_

#include "mem/allocator.hpp"
#include "result.hpp"
#include "slice.hpp"

namespace core {

template<typename T>
struct DynArray {
	Allocator _alloc = {0,0};
	usize _length    = 0;
	usize _capacity  = 0;
	T* _data         = nullptr;

	constexpr
	usize len() const {
		return _length;
	}

	constexpr
	usize cap() const {
		return _capacity;
	}

	usize pop(){
		if(_length == 0){ return 0; }

		_data[_length - 1].~T();
		_length -= 1;
		return _length;
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

		T* p = _data;
		new (&p[_length]) T(static_cast<T>(forward<U>(e)));
		_length += 1;
		return _length;
	}

	template<typename U>
	usize insert(usize idx, U&& e){
		if(idx > _length){
			debug_panic("Index out of bounds");
			return _length;
		}

		auto old_len = _length;
		if(append(forward<U>(e)) == old_len){
			debug_panic("Could not insert element");
			return _length;
		}

		// Insert at end is same as appending

		for(usize i = _length - 1; i > idx; i -= 1){
			core::swap(_data[i], _data[i-1]);
		}

		return _length;
	}

	// TODO: realloc()
	bool _expand_cap(usize new_size){
		T* new_data = static_cast<T*>(_alloc.alloc(new_size * sizeof(T)));

		if(new_data == nullptr){
			return false;
		}

		T* old_data = _data;

		for(usize i = 0; i < _length; i += 1){
			new (&new_data[i]) T(core::move(old_data[i]));
		}

		destroy(_alloc, _data);

		_data = new_data;
		_capacity = new_size;
		return true;
	}

	Slice<T> slice(usize from, usize to){
		auto s = Slice<T>(_data, _length);
		return s.slice(from, to);
	}

	Slice<T> as_slice(){
		return Slice<T>(_data, _length);
	}

	DynArray(){}

	DynArray(Allocator al) {
		_alloc = al;

		T* data_ptr = static_cast<T*>(_alloc.alloc(DynArray<T>::default_size * sizeof(T)));

		Assert(data_ptr != nullptr);
		// *this = DynArray();
		_data = data_ptr;
		_capacity = default_size;
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

	bool operator==(DynArray<T> const& arr) const {
		if(_length != arr._length){ return false; }

		for(usize i = 0; i < _length; i += 1){
			if(_data[i] != arr._data[i]){ return false; }
		}

		return true;
	}

	bool operator!=(DynArray<T> const& arr) const {
		return ! operator==(arr);
	}
};

}

#endif /* Include guard */
