#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Math.h"

namespace ee
{
	class EE_UTILITY_EXPORT Vector2
	{
	public:
		Vector2()
			:x(0.0f), y(0.0f)
		{ }

		Vector2(float x, float y)
			:x(x), y(y)
		{ }

		/** Exchange the contents of this vector with another. */
		void Swap(Vector2& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
		}

		float operator[] (UINT32 i) const
		{
			assert(i < 2);

			return *(&x + i);
		}

		float& operator[] (UINT32 i)
		{
			assert(i < 2);

			return *(&x + i);
		}

		/** Pointer accessor for direct copying. */
		float* Ptr()
		{
			return &x;
		}

		/** Pointer accessor for direct copying. */
		const float* Ptr() const
		{
			return &x;
		}

		Vector2& operator= (const Vector2& rhs)
		{
			x = rhs.x;
			y = rhs.y;

			return *this;
		}

		Vector2& operator= (float rhs)
		{
			x = rhs;
			y = rhs;

			return *this;
		}

		bool operator== (const Vector2& rhs) const
		{
			return (x == rhs.x && y == rhs.y);
		}

		bool operator!= (const Vector2& rhs) const
		{
			return (x != rhs.x || y != rhs.y);
		}

		Vector2 operator+ (const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2 operator- (const Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2 operator* (const float rhs) const
		{
			return Vector2(x * rhs, y * rhs);
		}

		Vector2 operator* (const Vector2& rhs) const
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		Vector2 operator/ (const float rhs) const
		{
			assert(rhs != 0.0);

			float fInv = 1.0f / rhs;

			return Vector2(x * fInv, y * fInv);
		}

		Vector2 operator/ (const Vector2& rhs) const
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		const Vector2& operator+ () const
		{
			return *this;
		}

		Vector2 operator- () const
		{
			return Vector2(-x, -y);
		}

		friend Vector2 operator* (float lhs, const Vector2& rhs)
		{
			return Vector2(lhs * rhs.x, lhs * rhs.y);
		}

		friend Vector2 operator/ (float lhs, const Vector2& rhs)
		{
			return Vector2(lhs / rhs.x, lhs / rhs.y);
		}

		friend Vector2 operator+ (Vector2& lhs, float rhs)
		{
			return Vector2(lhs.x + rhs, lhs.y + rhs);
		}

		friend Vector2 operator+ (float lhs, const Vector2& rhs)
		{
			return Vector2(lhs + rhs.x, lhs + rhs.y);
		}

		friend Vector2 operator- (const Vector2& lhs, float rhs)
		{
			return Vector2(lhs.x - rhs, lhs.y - rhs);
		}

		friend Vector2 operator- (const float lhs, const Vector2& rhs)
		{
			return Vector2(lhs - rhs.x, lhs - rhs.y);
		}

		Vector2& operator+= (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Vector2& operator+= (float rhs)
		{
			x += rhs;
			y += rhs;

			return *this;
		}

		Vector2& operator-= (const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		Vector2& operator-= (float rhs)
		{
			x -= rhs;
			y -= rhs;

			return *this;
		}

		Vector2& operator*= (float rhs)
		{
			x *= rhs;
			y *= rhs;

			return *this;
		}

		Vector2& operator*= (const Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;

			return *this;
		}

		Vector2& operator/= (float rhs)
		{
			assert(rhs != 0.0f);

			float inv = 1.0f / rhs;

			x *= inv;
			y *= inv;

			return *this;
		}

		Vector2& operator/= (const Vector2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;

			return *this;
		}

		/** Returns the length (magnitude) of the vector. */
		float Length() const
		{
			return Math::Sqrt(x * x + y * y);
		}

		/** Returns the square of the length(magnitude) of the vector. */
		float SquaredLength() const
		{
			return x * x + y * y;
		}

		/** Returns the distance to another vector. */
		float Distance(const Vector2& rhs) const
		{
			return (*this - rhs).Length();
		}

		/** Returns the square of the distance to another vector. */
		float SqrdDistance(const Vector2& rhs) const
		{
			return (*this - rhs).SquaredLength();
		}

		/** Calculates the dot (scalar) product of this vector with another. */
		float Dot(const Vector2& vec) const
		{
			return x * vec.x + y * vec.y;
		}

		/** Normalizes the vector. */
		float Normalize()
		{
			float len = Math::Sqrt(x * x + y * y);

			// Will also work for zero-sized vectors, but will change nothing
			if (len > 1e-08)
			{
				float invLen = 1.0f / len;
				x *= invLen;
				y *= invLen;
			}

			return len;
		}

		/** Generates a vector perpendicular to this vector. */
		Vector2 Perpendicular() const
		{
			return Vector2(-y, x);
		}

		/**
		* Calculates the 2 dimensional cross-product of 2 vectors, which results in a single floating point value which
		* is 2 times the area of the triangle.
		*/
		float Cross(const Vector2& other) const
		{
			return x * other.y - y * other.x;
		}

		/** Sets this vector's components to the minimum of its own and the ones of the passed in vector. */
		void Floor(const Vector2& cmp)
		{
			if (cmp.x < x) x = cmp.x;
			if (cmp.y < y) y = cmp.y;
		}

		/** Sets this vector's components to the maximum of its own and the ones of the passed in vector. */
		void Ceil(const Vector2& cmp)
		{
			if (cmp.x > x) x = cmp.x;
			if (cmp.y > y) y = cmp.y;
		}

		/** Returns true if this vector is zero length. */
		bool IsZeroLength() const
		{
			float sqlen = (x * x) + (y * y);
			return (sqlen < (1e-06 * 1e-06));
		}

		/** Calculates a reflection vector to the plane with the given normal. */
		Vector2 Reflect(const Vector2& normal) const
		{
			return Vector2(*this - (2 * this->Dot(normal) * normal));
		}

		/** Performs Gram-Schmidt orthonormalization. */
		static void Orthonormalize(Vector2& u, Vector2& v)
		{
			u.Normalize();

			float dot = u.Dot(v);
			v -= u * dot;
			v.Normalize();
		}

		/** Normalizes the provided vector and returns a new normalized instance. */
		static Vector2 Normalize(const Vector2& val)
		{
			float len = Math::Sqrt(val.x * val.x + val.y * val.y);

			// Will also work for zero-sized vectors, but will change nothing
			Vector2 normalizedVec = val;
			if (len > 1e-08)
			{
				float invLen = 1.0f / len;
				normalizedVec.x *= invLen;
				normalizedVec.y *= invLen;
			}

			return normalizedVec;
		}

		/** Checks are any of the vector components NaN. */
		bool isNaN() const
		{
			return Math::IsNaN(x) || Math::IsNaN(y);
		}

		/** Returns the minimum of all the vector components as a new vector. */
		static Vector2 min(const Vector2& a, const Vector2& b)
		{
			return Vector2(std::min(a.x, b.x), std::min(a.y, b.y));
		}

		/** Returns the maximum of all the vector components as a new vector. */
		static Vector2 max(const Vector2& a, const Vector2& b)
		{
			return Vector2(std::max(a.x, b.x), std::max(a.y, b.y));
		}

	public:
		static const Vector2 ZERO;
		static const Vector2 ONE;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;

	public:
		float x;
		float y;
	};
}