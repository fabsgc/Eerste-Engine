#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Degree.h"
#include "../Math/Math.h"

namespace ee
{
	Degree::Degree(const Radian& r)
		:_deg(r.valueDegrees())
	{
	}

	Degree Degree::wrap()
	{
		_deg = fmod(_deg, 360.0f);

		if (_deg < 0)
			_deg += 360.0f;

		return *this;
	}

	Degree& Degree::operator= (const Radian& r)
	{
		_deg = r.valueDegrees(); return *this;
	}

	Degree Degree::operator+ (const Radian& r) const
	{
		return Degree(_deg + r.valueDegrees());
	}

	Degree& Degree::operator+= (const Radian& r)
	{
		_deg += r.valueDegrees(); return *this;
	}

	Degree Degree::operator- (const Radian& r) const
	{
		return Degree(_deg - r.valueDegrees());
	}

	Degree& Degree::operator-= (const Radian& r)
	{
		_deg -= r.valueDegrees(); return *this;
	}

	float Degree::valueRadians() const
	{
		return _deg * Math::DEG2RAD;
	}
}
