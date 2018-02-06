#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"

namespace ee
{
	template<class T>
	class Module
	{
	public:
		template<class SubType, class ...Args>
		static void StartUp(Args &&...args)
		{
			static_assert(std::is_base_of<T, SubType>::value, "Provided type is not derived from type the Module is initialized with.");
			_instance() = new T(args);
		}

		static T& Instance() { return *_instance(); }
		static T* InstancePtr() { return _instance(); }

		virtual void Initialise() {};

	protected:
		Module() {}
		virtual ~Module() {}

		Module(const Module&) { }
		Module& operator=(const Module&) { return *this; }

		static T*& _instance()
		{
			static T* inst = nullptr;
			return inst;
		}

	};
}