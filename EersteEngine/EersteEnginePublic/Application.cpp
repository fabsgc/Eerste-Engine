#include "Application.h"

namespace ee
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	Application& gApplication()
	{
		return static_cast<Application&>(Application::Instance());
	}
}