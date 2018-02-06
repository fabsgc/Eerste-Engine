#pragma once

#include "../Prerequisites/Types.h"

#include <atomic>
#include <limits>
#include <new>
#include <utility>

#if EE_PLATFORM == BS_PLATFORM_LINUX
	#include <malloc.h>
#endif

namespace ee
{
	class BasicAllocator
	{
	public:
		UINT8 * alloc(UINT32 amount)
		{
			return (UINT8*)malloc(amount);
		}

		void free(void* data)
		{
			::free(data);
		}

		void clear()
		{
		}
	};
}
