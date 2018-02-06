#pragma once

// Platform options
#define EE_PLATFORM_WIN32 1
#define EE_PLATFORM_LINUX 2
#define EE_PLATFORM_OSX 3
#define EE_PLATFORM_IOS 4
#define EE_PLATFORM_ANDROID 5

// Compiler options
#define EE_COMPILER_MSVC 1
#define EE_COMPILER_GNUC 2
#define EE_COMPILER_INTEL 3
#define EE_COMPILER_CLANG 4

// Architecture options
#define EE_ARCHITECTURE_x86_32 1
#define EE_ARCHITECTURE_x86_64 2

// Finds current compiler
#if defined(__clang__)
#	define EE_COMPILER EE_COMPILER_CLANG
#	define EE_COMP_VER __clang_version__
#	define EE_THREADLOCAL __thread
#	define EE_STDCALL __attribute__((stdcall))
#	define EE_CDECL __attribute__((cdecl))
#elif defined(__GNUC__) // Check after Clang, as Clang defines this too
#	define EE_COMPILER EE_COMPILER_GNUC
#	define EE_COMP_VER (((__GNUC__)*100) + \
		(__GNUC_MINOR__*10) + \
		__GNUC_PATCHLEVEL__)
#	define EE_THREADLOCAL __thread
#	define EE_STDCALL __attribute__((stdcall))
#	define EE_CDECL __attribute__((cdecl))
#elif defined (__INTEL_COMPILER)
#	define EE_COMPILER EE_COMPILER_INTEL
#	define EE_COMP_VER __INTEL_COMPILER
#	define EE_STDCALL __stdcall
#	define EE_CDECL __cdecl
#elif defined(_MSC_VER)
#	define EE_COMPILER EE_COMPILER_MSVC
#	define EE_COMP_VER _MSC_VER
#	define EE_THREADLOCAL __declspec(thread)
#	define EE_STDCALL __stdcall
#	define EE_CDECL __cdecl
#	undef __PRETTY_FUNCTION__
#	define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#	pragma error "No known compiler. "
#endif

// Finds current platform
#if defined( __WIN32__ ) || defined( _WIN32 )
#	define EE_PLATFORM EE_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#	define EE_PLATFORM EE_PLATFORM_OSX
#else
#	define EE_PLATFORM EE_PLATFORM_LINUX
#endif

// Finds architecture type
#if defined(__x86_64__) || defined(_M_X64)
#	define EE_ARCH_TYPE EE_ARCHITECTURE_x86_64
#else
#	define EE_ARCH_TYPE EE_ARCHITECTURE_x86_32
#endif

// DLL export
#if EE_PLATFORM == EE_PLATFORM_WIN32
#	if EE_COMPILER == EE_COMPILER_MSVC
#		if defined(EE_STATIC_LIB)
#			define EE_UTILITY_EXPORT
#		else
#			if defined(EE_UTILITY_EXPORTS)
#				define EE_UTILITY_EXPORT __declspec(dllexport)
#			else
#				define EE_UTILITY_EXPORT __declspec(dllimport)
#			endif
#		endif
#	else
#		if defined(EE_STATIC_LIB)
#			define EE_UTILITY_EXPORT
#		else
#			if defined(EE_UTILITY_EXPORTS)
#				define EE_UTILITY_EXPORT __attribute__ ((dllexport))
#			else
#				define EE_UTILITY_EXPORT __attribute__ ((dllimport))
#			endif
#		endif
#	endif
#	define EE_UTILITY_HIDDEN
#else // Linux/Mac settings
#	define EE_UTILITY_EXPORT __attribute__ ((visibility ("default")))
#	define EE_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif