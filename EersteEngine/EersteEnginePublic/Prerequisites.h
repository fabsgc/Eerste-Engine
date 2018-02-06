#pragma once

#include "PrerequisitesCore.h"

// DLL export
#if EE_PLATFORM == EE_PLATFORM_WIN32
#	if EE_COMPILER == EE_COMPILER_MSVC
#		if defined(EE_STATIC_LIB)
#			define EE_EXPORT
#		else
#			if defined(EE_EXPORTS)
#				define EE_EXPORT __declspec(dllexport)
#			else
#				define EE_EXPORT __declspec(dllimport)
#			endif
#		endif
#	else
#		if defined(EE_STATIC_LIB)
#			define EE_EXPORT
#		else
#			if defined(EE_EXPORTS)
#				define EE_EXPORT __attribute__ ((dllexport))
#			else
#				define EE_EXPORT __attribute__ ((dllimport))
#			endif
#		endif
#	endif
#	define EE_HIDDEN
#else // Linux/Mac settings
#	define EE_EXPORT __attribute__ ((visibility ("default")))
#	define EE_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

namespace ee
{
}