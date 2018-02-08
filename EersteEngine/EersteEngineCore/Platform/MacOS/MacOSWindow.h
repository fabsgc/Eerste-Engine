#pragma once

#include "../Window.h"

namespace ee
{
	class EE_CORE_EXPORT MacOSWindow : public Window
	{
	public:
		MacOSWindow(const WINDOW_DESC& desc);
		~MacOSWindow();

		void Initialise() override;
		void Update() override;
	};
}