#include "CoreApplication.h"

namespace ee
{
	CoreApplication::CoreApplication(const START_UP_DESC& desc)
		: _renderer(nullptr)
		, _renderAPI(nullptr)
	{
	}

	CoreApplication::~CoreApplication()
	{
	}

	void CoreApplication::RunMainLoop()
	{
		_runMainLoop = true;

		while (_runMainLoop)
		{
		}
	}

	void CoreApplication::StopMainLoop()
	{
		_runMainLoop = false;
	}

	void CoreApplication::OnStartUp()
	{
	}

	void CoreApplication::OnShutDown()
	{
	}

	void CoreApplication::StartUpRenderAPI()
	{
	}

	void CoreApplication::StartUpRenderer()
	{
	}

	void CoreApplication::StartUpWindow()
	{
	}

	CoreApplication& gCoreApplication()
	{
		return CoreApplication::Instance();
	}
}