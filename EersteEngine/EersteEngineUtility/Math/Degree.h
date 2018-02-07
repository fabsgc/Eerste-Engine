#pragma once

#include "../Prerequisites/PlatformDefines.h"

namespace ee
{
	class Radian;

	class EE_UTILITY_EXPORT Degree
	{
	public:
		explicit Degree(float d = 0.0f) : _deg(d) {}
		Degree(const Radian& r);
		Degree& operator= (const float& f) { _deg = f; return *this; }
		Degree& operator= (const Degree& d) { _deg = d._deg; return *this; }
		Degree& operator= (const Radian& r);

		float valueDegrees() const { return _deg; }
		float valueRadians() const;
		Degree wrap();

		const Degree& operator+ () const { return *this; }
		Degree operator+ (const Degree& d) const { return Degree(_deg + d._deg); }
		Degree operator+ (const Radian& r) const;
		Degree& operator+= (const Degree& d) { _deg += d._deg; return *this; }
		Degree& operator+= (const Radian& r);
		Degree operator- () const { return Degree(-_deg); }
		Degree operator- (const Degree& d) const { return Degree(_deg - d._deg); }
		Degree operator- (const Radian& r) const;
		Degree& operator-= (const Degree& d) { _deg -= d._deg; return *this; }
		Degree& operator-= (const Radian& r);
		Degree operator* (float f) const { return Degree(_deg * f); }
		Degree operator* (const Degree& f) const { return Degree(_deg * f._deg); }
		Degree& operator*= (float f) { _deg *= f; return *this; }
		Degree operator/ (float f) const { return Degree(_deg / f); }
		Degree& operator/= (float f) { _deg /= f; return *this; }

		friend Degree operator* (float lhs, const Degree& rhs) { return Degree(lhs * rhs._deg); }
		friend Degree operator/ (float lhs, const Degree& rhs) { return Degree(lhs / rhs._deg); }
		friend Degree operator+ (Degree& lhs, float rhs) { return Degree(lhs._deg + rhs); }
		friend Degree operator+ (float lhs, const Degree& rhs) { return Degree(lhs + rhs._deg); }
		friend Degree operator- (const Degree& lhs, float rhs) { return Degree(lhs._deg - rhs); }
		friend Degree operator- (const float lhs, const Degree& rhs) { return Degree(lhs - rhs._deg); }

		bool operator<  (const Degree& d) const { return _deg <  d._deg; }
		bool operator<= (const Degree& d) const { return _deg <= d._deg; }
		bool operator== (const Degree& d) const { return _deg == d._deg; }
		bool operator!= (const Degree& d) const { return _deg != d._deg; }
		bool operator>= (const Degree& d) const { return _deg >= d._deg; }
		bool operator>  (const Degree& d) const { return _deg >  d._deg; }

	private:
		float _deg;
	};
}