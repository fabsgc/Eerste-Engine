#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"

namespace ee
{
	template<class T>
	class Module
	{
	public:
		template<class ...Args>
		static void StartUp(Args &&...args)
		{
			EE_ASSERT_ERROR(!IsStartedUp(), "Trying to start an already started module.");

			_instance() = new T(std::forward<Args>(args)...);
			IsStartedUp() = true;

			((Module*)_instance())->OnStartUp();
		}

		template<class SubType, class ...Args>
		static void StartUp(Args &&...args)
		{
			static_assert(std::is_base_of<T, SubType>::value, "Provided type is not derived from type the Module is initialized with.");
			EE_ASSERT_ERROR(!IsStartedUp(), "Trying to start an already started module.");

			_instance() = new SubType(std::forward<Args>(args)...);
			IsStartedUp() = true;

			((Module*)_instance())->OnStartUp();
		}

		static void ShutDown()
		{
			EE_ASSERT_ERROR(IsDestroyed(), "Trying to shut down an already shut down module.");
			EE_ASSERT_ERROR(!IsStartedUp(), "Trying to shut down a module which was never started.");

			((Module*)_instance())->OnShutDown();

			delete _instance();
			IsDestroyed() = true;
		}

		static bool IsStarted()
		{
			return IsStartedUp() && !IsDestroyed();
		}

		static T& Instance() 
		{ 
			EE_ASSERT_ERROR(IsStartedUp(), "Trying to access a module but it hasn't been started up yet.");
			EE_ASSERT_ERROR(!IsDestroyed(), "Trying to access a destroyed module.");

			return *_instance(); 
		}
		static T* InstancePtr() 
		{ 
			EE_ASSERT_ERROR(IsStartedUp(), "Trying to access a module but it hasn't been started up yet.");
			EE_ASSERT_ERROR(!IsDestroyed(), "Trying to access a destroyed module.");

			return _instance(); 
		}

		virtual void Initialise() {};

	protected:
		Module() {}
		virtual ~Module() {}

		Module(Module const&) {};
		Module& operator=(const Module&) { return *this; }

		virtual void OnStartUp() {}
		virtual void OnShutDown() {}

		static T*& _instance()
		{
			static T* inst = nullptr;
			return inst;
		}

		static bool& IsDestroyed()
		{
			static bool inst = false;
			return inst;
		}

		static bool& IsStartedUp()
		{
			static bool inst = false;
			return inst;
		}
	};
}