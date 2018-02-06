#pragma once

#include "CoreApplication.h"
#include "Prerequisites.h"

namespace ee
{
	class Application: public CoreApplication
	{
	public:
		Application();
		virtual ~Application();
	};

	EE_EXPORT Application& gApplication();
}