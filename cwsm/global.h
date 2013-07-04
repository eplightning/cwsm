#ifndef _H_CWSM_GLOBAL
#define _H_CWSM_GLOBAL

#if defined(_WIN32) || defined(_WIN64)
	#define CWSM_PLATFORM_WINDOWS
	#define _WIN32_WINNT 0x0502

	#include <windows.h>
#endif

#ifndef _MSC_VER
	#include <cstdint>
#endif

/**
 * Integer types
 */

#ifdef _MSC_VER
	typedef signed char int8;
	typedef unsigned char uint8;
	typedef unsigned char byte;
	typedef unsigned __int64 uint64;
	typedef unsigned __int32 uint32;
	typedef unsigned __int16 uint16;
	typedef __int64 int64;
	typedef __int32 int32;
	typedef __int16 int16;
	typedef UINT_PTR uptr;
#else
	typedef signed char int8;
	typedef unsigned char uint8;
	typedef unsigned char byte;
	typedef uint64_t uint64;
	typedef uint32_t uint32;
	typedef uint16_t uint16;
	typedef int64_t int64;
	typedef int32_t int32;
	typedef int16_t int16;
	typedef uintptr_t uptr;
#endif

#endif