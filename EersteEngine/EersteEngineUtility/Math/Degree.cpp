#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Degree.h"
#include "../Math/Math.h"

namespace ee
{
	Degree::Degree(const Radian& r)
		:_deg(r.ValueDegrees())
	{
	}

	Degree Degree::Wrap()
	{
		_deg = fmod(_deg, 360.0f);

		if (_deg < 0)
			_deg += 360.0f;

		return *this;
	}

	Degree& Degree::operator= (const Radian& r)
	{
		_deg = r.ValueDegrees(); return *this;
	}

	Degree Degree::operator+ (const Radian& r) const
	{
		return Degree(_deg + r.ValueDegrees());
	}

	Degree& Degree::operator+= (const Radian& r)
	{
		_deg += r.ValueDegrees(); return *this;
	}

	Degree Degree::operator- (const Radian& r) const
	{
		return Degree(_deg - r.ValueDegrees());
	}

	Degree& Degree::operator-= (const Radian& r)
	{
		_deg -= r.ValueDegrees(); return *this;
	}

	float Degree::ValueRadians() const
	{
		return _deg * Math::DEG2RAD;
	}
}
