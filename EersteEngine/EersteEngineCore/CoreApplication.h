#pragma once

#include "CorePrerequisites.h"
#include "Utility/IModule.h"
#include "Utility/DynamicLib.h"
#include "Utility/DynamicLibManager.h"
#include "Platform\Window.h"

namespace ee
{
	struct START_UP_DESC
	{
		String RenderAPI;
		String Renderer;

		START_UP_DESC()
			: RenderAPI("EersteEngineD3D11RenderAPI")
			, Renderer("EersteEngineRendererEE")
		{
		}
	};

	class EE_CORE_EXPORT CoreApplication : public IModule<CoreApplication>
	{
	public:
		 CoreApplication(const START_UP_DESC& desc);
		 virtual ~CoreApplication();

		 void RunMainLoop();
		 void StopMainLoop();

		template<class T = CoreApplication>
		static void StartUp(const START_UP_DESC& desc)
		{
			IModule::StartUp<T>(desc);
		}

	protected:
		 void OnStartUp() override;
		 void OnShutDown() override;

		 void StartUpRenderAPI();
		 void StartUpRenderer();
		 void StartUpWindow();

	private:
		volatile bool _runMainLoop;

		START_UP_DESC _startUpDesc;

		SPtr<DynamicLib> _renderer;
		SPtr<DynamicLib> _renderAPI;
		SPtr<Window>     _window;
	};

	EE_CORE_EXPORT CoreApplication& gCoreApplication();
}