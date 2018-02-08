#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Radian.h"
#include "../Math/Math.h"

namespace ee
{
	Radian::Radian(const Degree& d) : _rad(d.ValueRadians())
	{ }

	Radian Radian::Wrap()
	{
		_rad = fmod(_rad, Math::TWO_PI);

		if (_rad < 0)
			_rad += Math::TWO_PI;

		return *this;
	}

	Radian& Radian::operator= (const Degree& d)
	{
		_rad = d.ValueRadians();
		return *this;
	}

	Radian Radian::operator+ (const Degree& d) const
	{
		return Radian(_rad + d.ValueRadians());
	}

	Radian& Radian::operator+= (const Degree& d)
	{
		_rad += d.ValueRadians();
		return *this;
	}

	Radian Radian::operator- (const Degree& d) const
	{
		return Radian(_rad - d.ValueRadians());
	}

	Radian& Radian::operator-= (const Degree& d)
	{
		_rad -= d.ValueRadians();
		return *this;
	}

	float Radian::ValueDegrees() const
	{
		return _rad * Math::RAD2DEG;
	}
}
