/* IMPORTANT: Always include this *after* system headers such as <windows.h> or <unistd.h> */

#ifndef _context_hpp_include_
#define _context_hpp_include_

#include "types.hpp"

namespace context {

enum struct OS {
	Linux, OpenBSD, FreeBSD, Windows,
};

constexpr OS os =
#if defined(__linux__)
	OS::Linux
#elif defined(_WIN32)
	OS::Windows
#elif defined(__OpenBSD__)
	OS::OpenBSD
#elif defined(__FreeBSD__)
	OS::FreeBSD
#endif
;

constexpr auto os_name =
#if defined(__linux__)
	"Linux"
#elif defined(_WIN32)
	"Windows"
#elif defined(__OpenBSD__)
	"OpenBSD"
#elif defined(__FreeBSD__)
	"FreeBSD"
#endif
;

#if defined(_POSIX_VERSION)
constexpr usize posix_version = _POSIX_VERSION;
#else
constexpr usize posix_version = 0;
#endif

}

#endif /* Include guard */
