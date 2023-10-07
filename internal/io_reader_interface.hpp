#include "types.hpp"
#include "slice.hpp"

struct Reader {
	struct VTable {
		usize (*read)(void * impl, core::Slice<byte> buf);
	};
	void * _impl;
	const VTable * _vtable;
	usize read(core::Slice<byte> buf){
		return _vtable->read(_impl, buf);
	}
	template<typename _Impl>
	static constexpr
	VTable vtable_helper = {
		.read = [](void * impl, core::Slice<byte> buf) -> usize {
			auto obj = reinterpret_cast<_Impl *>(impl);
			return obj->read(buf);
		}
	};
};
template<typename _Impl>
auto make_reader(_Impl* impl){
	static constexpr const auto vt = Reader::vtable_helper<_Impl>;
	return Reader{
		._impl = impl,
		._vtable = &vt,
	};
}
