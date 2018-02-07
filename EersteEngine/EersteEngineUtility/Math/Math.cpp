#include "../Math/Math.h"

namespace ee
{
	const float Math::LOG2 = std::log(2.0f);

	Radian Math::acos(float val)
	{
		if (-1.0f < val)
		{
			if (val < 1.0f)
				return Radian(std::acos(val));
			else
				return Radian(0.0f);
		}
		else
		{
			return Radian(PI);
		}
	}

	Radian Math::asin(float val)
	{
		if (-1.0f < val)
		{
			if (val < 1.0f)
				return Radian(std::asin(val));
			else
				return Radian(HALF_PI);
		}
		else
		{
			return Radian(-HALF_PI);
		}
	}

	float Math::sign(float val)
	{
		if (val > 0.0f)
			return 1.0f;

		if (val < 0.0f)
			return -1.0f;

		return 0.0f;
	}

	float Math::invSqrt(float val)
	{
		return 1.0f / sqrt(val);
	}
}