#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Utility/Module.h"
#include "../Utility/DynamicLibrary.h"

namespace ee
{
	class DynamicLibraryManager : public Module<DynamicLibraryManager>
	{
	public:
		EE_UTILITY_EXPORT DynamicLibraryManager();
		EE_UTILITY_EXPORT virtual ~DynamicLibraryManager();

		EE_UTILITY_EXPORT DynamicLibrary *Load(const String& name);
		EE_UTILITY_EXPORT void Unload(DynamicLibrary* lib);

	protected:
		Map<String, DynamicLibrary*> _loadedLibraries;
	};

	EE_UTILITY_EXPORT DynamicLibraryManager& gDynamicLibraryManager();
}