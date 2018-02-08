#pragma once

#include "../Window.h"

namespace ee
{
	class EE_CORE_EXPORT Win32Window: public Window
	{
	public:
		Win32Window(const WINDOW_DESC& desc);
		~Win32Window();

		void Initialise() override;
		void Update() override;
	};
}