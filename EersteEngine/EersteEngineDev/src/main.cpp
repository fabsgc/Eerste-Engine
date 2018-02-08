#include "CorePrerequisites.h"
#include "CoreApplication.h"

#if EE_PLATFORM == EE_PLATFORM_WIN32
	#include <windows.h>
#endif

using namespace ee;

#if EE_PLATFORM == EE_PLATFORM_WIN32
int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
)
#else
int main()
#endif
{
	START_UP_DESC desc;

	desc.RenderAPI = EE_RENDER_API;
	desc.Renderer = EE_RENDERER;

	CoreApplication::StartUp(desc);
	CoreApplication& app = gCoreApplication();

	app.RunMainLoop();
	app.ShutDown();
}