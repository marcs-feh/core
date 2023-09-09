/* IMPORTANT: Always include this *after* system headers such as <windows.h> or <unistd.h> */

#ifndef _context_hpp_include_
#define _context_hpp_include_

#include "types.hpp"

namespace core {
namespace platform {

enum struct OS : u8 {
	Linux, OpenBSD, Windows,
};

constexpr OS os =
#if defined(__linux__)
	OS::Linux;
#elif defined(_WIN32)
	OS::Windows;
#elif defined(__OpenBSD__)
	OS::OpenBSD;
#endif

constexpr usize posix_version = 
#if defined(_POSIX_VERSION)
	_POSIX_VERSION;
#else
	0;
#endif

}}

#endif /* Include guard */
