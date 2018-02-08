#include "CoreApplication.h"

#include "Platform\Win32\Win32Window.h"
#include "Platform\Linux\LinuxWindow.h"
#include "Platform\MacOS\MacOSWindow.h"

namespace ee
{
	CoreApplication::CoreApplication(const START_UP_DESC& desc)
		: _renderer(nullptr)
		, _renderAPI(nullptr)
		, _startUpDesc(desc)
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
			_window->Update();
		}
	}

	void CoreApplication::StopMainLoop()
	{
		_runMainLoop = false;
	}

	void CoreApplication::OnStartUp()
	{
		DynamicLibManager::StartUp();

		StartUpRenderAPI();
		StartUpRenderer();
		StartUpWindow();
	}

	void CoreApplication::OnShutDown()
	{
	}

	void CoreApplication::StartUpRenderAPI()
	{
		_renderAPI = gDynamicLibManager().Load(_startUpDesc.RenderAPI);
	}

	void CoreApplication::StartUpRenderer()
	{
		_renderAPI = gDynamicLibManager().Load(_startUpDesc.Renderer);
	}

	void CoreApplication::StartUpWindow()
	{
		WINDOW_DESC desc;
		desc.Width  = 1280;
		desc.Height = 720;
		desc.Title  = L"My first application";

#if EE_PLATFORM == EE_PLATFORM_WIN32
		_window.reset(new Win32Window(desc));
#elif EE_PLATFORM == EE_PLATFORM_MACOS
		_window.reset(new MacOSWindow(desc));
#else
		_window.reset(new LinuxWindow(desc));
#endif

		_window->Initialise();
	}

	CoreApplication& gCoreApplication()
	{
		return CoreApplication::Instance();
	}
}