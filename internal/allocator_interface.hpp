#include "types.hpp"

struct Allocator {
struct VTable {
void* (*alloc)(void * impl, usize nbytes);
void* (*alloc_undef)(void * impl, usize nbytes);
void (*free)(void * impl, void* ptr);
void (*free_all)(void * impl);
bool (*has_address)(void * impl, void* ptr);
};
void * _impl;
const VTable * _vtable;
void* alloc(usize nbytes){
return _vtable->alloc(_impl, nbytes);
}
void* alloc_undef(usize nbytes){
return _vtable->alloc_undef(_impl, nbytes);
}
void free(void* ptr){
return _vtable->free(_impl, ptr);
}
void free_all(){
return _vtable->free_all(_impl);
}
bool has_address(void* ptr){
return _vtable->has_address(_impl, ptr);
}
template<typename _Impl>
static constexpr
VTable vtable_helper = {
.alloc = [](void * impl, usize nbytes) -> void* {
auto obj = reinterpret_cast<_Impl *>(impl);
return obj->alloc(nbytes);
},
.alloc_undef = [](void * impl, usize nbytes) -> void* {
auto obj = reinterpret_cast<_Impl *>(impl);
return obj->alloc_undef(nbytes);
},
.free = [](void * impl, void* ptr) -> void {
auto obj = reinterpret_cast<_Impl *>(impl);
return obj->free(ptr);
},
.free_all = [](void * impl) -> void {
auto obj = reinterpret_cast<_Impl *>(impl);
return obj->free_all();
},
.has_address = [](void * impl, void* ptr) -> bool {
auto obj = reinterpret_cast<_Impl *>(impl);
return obj->has_address(ptr);
}
};
};
template<typename _Impl>
auto make_allocator(_Impl* impl){
static constexpr const auto vt = Allocator::vtable_helper<_Impl>;
return Allocator{
._impl = impl,
._vtable = &vt,
};
}