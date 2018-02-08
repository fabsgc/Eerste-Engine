#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Utility/IModule.h"
#include "../Utility/Timer.h"

namespace ee
{
	class EE_UTILITY_EXPORT Time: public IModule<Time>
	{
	public:
		Time();
		~Time();

		float GetTime() const { return _timeSinceStart; }
		UINT64 GetTimeMs() const { return _timeSinceStartMs; }
		float GetFrameDelta() const { return _frameDelta; }
		UINT64 GetFrameIdx() const { return _currentFrame.load(); }
		UINT64 GetTimePrecise() const;
		UINT64 GetStartTimeMs() const { return _appStartTime; }
		void Update();

	public:
		static const double MICROSEC_TO_SEC;

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