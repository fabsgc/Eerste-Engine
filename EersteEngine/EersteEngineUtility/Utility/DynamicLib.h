#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"

#if EE_PLATFORM == EE_PLATFORM_WIN32
	struct HINSTANCE__;
	typedef struct HINSTANCE__* hInstance;
#endif

namespace ee
{
#if EE_PLATFORM == EE_PLATFORM_WIN32
#    define DYNAMIC_LIB_HANDLE hInstance
#    define DYNAMIC_LIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNAMIC_LIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNAMIC_LIB_UNLOAD( a ) !FreeLibrary( a )
#elif EE_PLATFORM == EE_PLATFORM_LINUX || EE_PLATFORM == EE_PLATFORM_OSX
#    define DYNAMIC_LIB_HANDLE void*
#    define DYNAMIC_LIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNAMIC_LIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNAMIC_LIB_UNLOAD( a ) dlclose( a )
#endif

	class EE_UTILITY_EXPORT DynamicLib
	{
	public:
		DynamicLib(const String& name);
		~DynamicLib();

		void  Load();
		void  Unload();
		const String& getName() const { return _name; }
		void* GetSymbol(const String& strName) const;
	
	public:
		static const char* EXTENSION;
		static const char* PREFIX;

	protected:
		String DynamicLibError();

	protected:
		String             _name;
		DYNAMIC_LIB_HANDLE _handle;
	};
}