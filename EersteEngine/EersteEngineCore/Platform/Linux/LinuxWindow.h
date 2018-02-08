#pragma once

#include "../Window.h"

namespace ee
{
	class EE_CORE_EXPORT LinuxWindow : public Window
	{
	public:
		LinuxWindow(const WINDOW_DESC& desc);
		~LinuxWindow();

		void Initialise() override;
		void Update() override;
	};
}