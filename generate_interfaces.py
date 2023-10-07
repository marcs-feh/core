from tools.interfacer import interface


interface('Allocator', {
    'alloc: void*': ['nbytes: usize'],
    'alloc_undef: void*': ['nbytes: usize'],
    'free: void': ['ptr: void*'],
    'free_all: void': [],
    'has_address: bool': ['ptr: void*'],
}).generate_file('mem/internal/allocator_interface.hpp')
