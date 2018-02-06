#include "Application.h"

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

}