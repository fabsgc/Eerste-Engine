#pragma once

#include "../CorePrerequisites.h"
#include "Utility/IModule.h"

namespace ee
{
	struct EE_CORE_EXPORT WINDOW_DESC
	{
		UINT32 Width;
		UINT32 Height;

		WString Title;

		WINDOW_DESC()
			: Width((UINT32)1280)
			, Height((UINT32)720)
			, Title(L"Eerste Engine")
		{
		}
	};

	class EE_CORE_EXPORT Window: public IModule<Window>
	{
	public:
		Window(const WINDOW_DESC& desc);
		virtual ~Window() {};

		virtual void OnStartUp() {}
		virtual void OnShutDown() {}

		virtual void Initialise() {}
		virtual void Update() {}

	private:
		WINDOW_DESC _windowDesc;
	};
}