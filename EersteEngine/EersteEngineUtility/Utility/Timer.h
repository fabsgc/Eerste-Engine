#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"

namespace ee
{
	/** Timer class used for querying high precision timers. */
	class Timer
	{
	public:
		EE_UTILITY_EXPORT        Timer();
		EE_UTILITY_EXPORT void   Reset();
		EE_UTILITY_EXPORT UINT64 GetMilliseconds() const;
		EE_UTILITY_EXPORT UINT64 GetMicroseconds() const;
		EE_UTILITY_EXPORT UINT64 GetStartMs() const;

	private:
		std::chrono::high_resolution_clock                          _HRClock;
		std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
	};
}

