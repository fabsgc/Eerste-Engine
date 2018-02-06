#pragma once

#include "PrerequisitesCore.h"
#include "Utility/Module.h"

namespace ee
{
	class EE_CORE_EXPORT CoreApplication : public Module<CoreApplication>
	{
	public:
		CoreApplication();
		virtual ~CoreApplication();

	private:
		CoreApplication(CoreApplication const&) = delete;
		CoreApplication& operator=(CoreApplication const&) = delete;
	};

	EE_CORE_EXPORT CoreApplication& gCoreApplication();
}