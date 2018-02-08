#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Utility/IModule.h"
#include "../Utility/DynamicLib.h"

namespace ee
{
	class EE_UTILITY_EXPORT DynamicLibManager : public IModule<DynamicLibManager>
	{
	public:
		DynamicLibManager();
		virtual ~DynamicLibManager();

		SPtr<DynamicLib> Load(const String& name);
		void Unload(SPtr<DynamicLib> lib);

	protected:
		Map<String, SPtr<DynamicLib>> _loadedLibraries;
	};

	EE_UTILITY_EXPORT DynamicLibManager& gDynamicLibManager();
}