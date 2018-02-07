#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Utility/Module.h"
#include "../Utility/DynamicLib.h"

namespace ee
{
	class DynamicLibManager : public Module<DynamicLibManager>
	{
	public:
		EE_UTILITY_EXPORT DynamicLibManager();
		EE_UTILITY_EXPORT virtual ~DynamicLibManager();

		EE_UTILITY_EXPORT DynamicLib *Load(const String& name);
		EE_UTILITY_EXPORT void Unload(DynamicLib* lib);

	protected:
		Map<String, DynamicLib*> _loadedLibraries;
	};

	EE_UTILITY_EXPORT DynamicLibManager& gDynamicLibManager();
}