//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "../Utility/DynamicLibrary.h"

#if EE_PLATFORM == EE_PLATFORM_OSX
	#include <dlfcn.h>
#endif

namespace ee
{

#if EE_PLATFORM == EE_PLATFORM_LINUX
	const char* DynamicLibrary::EXTENSION = "so";
	const char* DynamicLibrary::PREFIX = "lib";
#elif EE_PLATFORM == EE_PLATFORM_OSX
	const char* DynamicLibrary::EXTENSION = "dylib";
	const char* DynamicLibrary::PREFIX = "lib";
#elif EE_PLATFORM == EE_PLATFORM_WIN32
	const char* DynamicLibrary::EXTENSION = "dll";
	const char* DynamicLibrary::PREFIX = nullptr;
#else
#error Unhandled platform
#endif

	DynamicLibrary::DynamicLibrary(const String& name)
		: _name(name)
		, _handle(nullptr)
	{
		Load();
	}

	DynamicLibrary::~DynamicLibrary()
	{
	}

	void DynamicLibrary::Load()
	{
		if (_handle)
			return;

		_handle = (DYNAMIC_LIB_HANDLE)DYNAMIC_LIB_LOAD(_name.c_str());

		if (!_handle)
		{
			String error = "Could not load dynamic library " + _name + ".  System Error: " + DynamicLibError();
			assert(!error.c_str());
		}
	}

	void DynamicLibrary::Unload()
	{
		if (!_handle)
			return;

		if (DYNAMIC_LIB_UNLOAD(_handle))
		{
			String error = "Could not unload dynamic library " + _name + ".  System Error: " + DynamicLibError();
			assert(!error.c_str());
		}
	}

	void* DynamicLibrary::GetSymbol(const String& strName) const
	{
		return nullptr;

	if (!_handle)
			return nullptr;

		return (void*)DYNAMIC_LIB_GETSYM(_handle, strName.c_str());
	}

	String DynamicLibrary::DynamicLibError()
	{
#if EE_PLATFORM == EE_PLATFORM_WIN32
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL
		);
		String ret = (char*)lpMsgBuf;
		// Free the buffer.
		LocalFree(lpMsgBuf);
		return ret;
#elif EE_PLATFORM == EE_PLATFORM_LINUX || EE_PLATFORM == EE_PLATFORM_OSX
		return String(dlerror());
#else
		return String("");
#endif
	}
}
