from tools.interfacer import interface


interface('Allocator', {
    '@include': ['types.hpp'],
    'alloc: void*': ['nbytes: usize'],
    'alloc_undef: void*': ['nbytes: usize'],
    'free: void': ['ptr: void*'],
    'free_all: void': [],
    'has_address: bool': ['ptr: void*'],
}).generate_file('internal/allocator_interface.hpp')

interface('Reader', {
    '@include': ['types.hpp', 'slice.hpp'],
    'read: usize': ['buf: core::Slice<byte>'],
}).generate_file('internal/io_reader_interface.hpp')
