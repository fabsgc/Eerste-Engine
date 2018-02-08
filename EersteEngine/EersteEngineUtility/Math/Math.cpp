#include "../Math/Math.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Quaternion.h"

namespace ee
{
	const float Math::LOG2 = std::log(2.0f);

	Radian Math::Acos(float val)
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

	Radian Math::Asin(float val)
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

	float Math::Sign(float val)
	{
		if (val > 0.0f)
			return 1.0f;

		if (val < 0.0f)
			return -1.0f;

		return 0.0f;
	}

	float Math::InvSqrt(float val)
	{
		return 1.0f / sqrt(val);
	}

	bool Math::ApproxEquals(const Vector2& a, const Vector2& b, float tolerance)
	{
		return fabs(b.x - a.x) <= tolerance && fabs(b.y - a.y) <= tolerance;
	}

	bool Math::ApproxEquals(const Vector3& a, const Vector3& b, float tolerance)
	{
		return fabs(b.x - a.x) <= tolerance && fabs(b.y - a.y) <= tolerance && fabs(b.z - a.z) <= tolerance;
	}

	bool Math::ApproxEquals(const Vector4& a, const Vector4& b, float tolerance)
	{
		return fabs(b.x - a.x) <= tolerance && fabs(b.y - a.y) <= tolerance && fabs(b.z - a.z) <= tolerance &&
			fabs(b.w - a.w) <= tolerance;
	}

	bool Math::ApproxEquals(const Quaternion& a, const Quaternion& b, float tolerance)
	{
		return fabs(b.x - a.x) <= tolerance && fabs(b.y - a.y) <= tolerance && fabs(b.z - a.z) <= tolerance &&
			fabs(b.w - a.w) <= tolerance;
	}
}