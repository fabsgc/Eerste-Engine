#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Utility/Module.h"
#include "../Utility/Timer.h"

namespace ee
{
	class Time: public Module<Time>
	{
	public:
		EE_UTILITY_EXPORT Time();
		EE_UTILITY_EXPORT ~Time();

		EE_UTILITY_EXPORT float GetTime() const { return _timeSinceStart; }
		EE_UTILITY_EXPORT UINT64 GetTimeMs() const { return _timeSinceStartMs; }
		EE_UTILITY_EXPORT float GetFrameDelta() const { return _frameDelta; }
		EE_UTILITY_EXPORT UINT64 GetFrameIdx() const { return _currentFrame.load(); }
		EE_UTILITY_EXPORT UINT64 GetTimePrecise() const;
		EE_UTILITY_EXPORT UINT64 GetStartTimeMs() const { return _appStartTime; }
		EE_UTILITY_EXPORT void Update();

	public:
		EE_UTILITY_EXPORT static const double MICROSEC_TO_SEC;

	private:
		float  _frameDelta;
		float  _timeSinceStart;
		UINT64 _timeSinceStartMs;

		UINT64 _appStartTime;
		UINT64 _lastFrameTime;
		std::atomic<unsigned long> _currentFrame;

		SPtr<Timer> _timer;
	};

	EE_UTILITY_EXPORT Time& gTime();
}