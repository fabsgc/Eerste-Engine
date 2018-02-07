#pragma once

#include "PrerequisitesCore.h"
#include "Utility/Module.h"
#include "Utility/DynamicLib.h"

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

	class CoreApplication : public Module<CoreApplication>
	{
	public:
		EE_CORE_EXPORT CoreApplication(const START_UP_DESC& desc);
		EE_CORE_EXPORT virtual ~CoreApplication();

		EE_CORE_EXPORT void RunMainLoop();
		EE_CORE_EXPORT void StopMainLoop();

		template<class T = CoreApplication>
		static void StartUp(const START_UP_DESC& desc)
		{
			Module::StartUp<T>(desc);
		}

	protected:
		EE_CORE_EXPORT void OnStartUp() override;
		EE_CORE_EXPORT void OnShutDown() override;

		EE_CORE_EXPORT void StartUpRenderAPI();
		EE_CORE_EXPORT void StartUpRenderer();
		EE_CORE_EXPORT void StartUpWindow();

	private:
		volatile bool _runMainLoop;

		SPtr<DynamicLib> _renderer;
		SPtr<DynamicLib> _renderAPI;
	};

	EE_CORE_EXPORT CoreApplication& gCoreApplication();
}