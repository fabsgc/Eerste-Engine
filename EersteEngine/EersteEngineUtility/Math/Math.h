#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Degree.h"
#include "../Math/Radian.h"

namespace ee
{
	class EE_UTILITY_EXPORT Math {
	public:
		/** Inverse cosine. */
		static Radian acos(float val);

		/** Inverse sine. */
		static Radian asin(float val);

		/** Inverse tangent. */
		static Radian atan(float val) { return Radian(std::atan(val)); }

		/** Inverse tangent with two arguments, returns angle between the X axis and the point. */
		static Radian atan2(float y, float x) { return Radian(std::atan2(y, x)); }

		/** Cosine. */
		static float cos(const Radian& val) { return (float)std::cos(val.valueRadians()); }

		/** Cosine. */
		static float cos(float val) { return (float)std::cos(val); }

		/** Sine. */
		static float sin(const Radian& val) { return (float)std::sin(val.valueRadians()); }

		/** Sine. */
		static float sin(float val) { return (float)std::sin(val); }

		/** Tangent. */
		static float tan(const Radian& val) { return (float)std::tan(val.valueRadians()); }

		/** Tangent. */
		static float tan(float val) { return (float)std::tan(val); }

		/** Square root. */
		static float sqrt(float val) { return (float)std::sqrt(val); }

		/** Square root. */
		static Radian sqrt(const Radian& val) { return Radian(std::sqrt(val.valueRadians())); }

		/** Square root. */
		static Degree sqrt(const Degree& val) { return Degree(std::sqrt(val.valueDegrees())); }

		/** Square root followed by an inverse. */
		static float invSqrt(float val);

		/** Returns square of the provided value. */
		static float sqr(float val) { return val * val; }

		/** Returns base raised to the provided power. */
		static float pow(float base, float exponent) { return (float)std::pow(base, exponent); }

		/** Returns euler number (e) raised to the provided power. */
		static float exp(float val) { return (float)std::exp(val); }

		/** Returns natural (base e) logarithm of the provided value. */
		static float log(float val) { return (float)std::log(val); }

		/** Returns base 2 logarithm of the provided value. */
		static float log2(float val) { return (float)(std::log(val) / LOG2); }

		/** Returns base N logarithm of the provided value. */
		static float logN(float base, float val) { return (float)(std::log(val) / std::log(base)); }

		/** Returns the sign of the provided value as 1 or -1. */
		static float sign(float val);

		/** Returns the sign of the provided value as 1 or -1. */
		static Radian sign(const Radian& val) { return Radian(sign(val.valueRadians())); }

		/** Returns the sign of the provided value as 1 or -1. */
		static Degree sign(const Degree& val) { return Degree(sign(val.valueDegrees())); }

		/** Returns the absolute value. */
		static float abs(float val) { return float(std::fabs(val)); }

		/** Returns the absolute value. */
		static Degree abs(const Degree& val) { return Degree(std::fabs(val.valueDegrees())); }

		/** Returns the absolute value. */
		static Radian abs(const Radian& val) { return Radian(std::fabs(val.valueRadians())); }

		/** Returns the nearest integer equal or higher to the provided value. */
		static float ceil(float val) { return (float)std::ceil(val); }

		/** Returns the nearest integer equal or higher to the provided value. */
		static int ceilToInt(float val) { return (int)std::ceil(val); }

		/** Returns the integer nearest to the provided value. */
		static float round(float val) { return (float)std::floor(val + 0.5f); }

		/** Returns the integer nearest to the provided value. */
		static int roundToInt(float val) { return (int)std::floor(val + 0.5f); }

		/** Checks if the value is a valid number. */
		static bool isNaN(float f)
		{
			return f != f;
		}

		/** Clamp a value within an inclusive range. */
		template <typename T>
		static T clamp(T val, T minval, T maxval)
		{
			assert(minval <= maxval && "Invalid clamp range");
			return std::max(std::min(val, maxval), minval);
		}

		static constexpr float POS_INFINITY = std::numeric_limits<float>::infinity();
		static constexpr float NEG_INFINITY = -std::numeric_limits<float>::infinity();
		static constexpr float PI = 3.14159265358979323846f;
		static constexpr float TWO_PI = (float)(2.0f * PI);
		static constexpr float HALF_PI = (float)(0.5f * PI);
		static constexpr float DEG2RAD = PI / 180.0f;
		static constexpr float RAD2DEG = 180.0f / PI;
		static const float LOG2;
	};
}