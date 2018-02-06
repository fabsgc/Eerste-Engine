#include "CoreApplication.h"

namespace ee
{
	CoreApplication::CoreApplication()
	{
	}

	CoreApplication::~CoreApplication()
	{
	}

	CoreApplication& gCoreApplication()
	{
		return CoreApplication::Instance();
	}
}