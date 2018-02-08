#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Vector3.h"

namespace ee
{
	/** A ray in 3D space represented with an origin and direction. */
	class EE_UTILITY_EXPORT Ray
	{
	public:
		Ray()
			:_origin(Vector3::ZERO), _direction(Vector3::UNIT_Z)
		{ }

		Ray(const Vector3& origin, const Vector3& direction)
			:_origin(origin), _direction(direction)
		{ }

		void SetOrigin(const Vector3& origin) { _origin = origin; }
		const Vector3& GetOrigin(void) const { return _origin; }

		void SetDirection(const Vector3& dir) { _direction = dir; }
		const Vector3& GetDirection(void) const { return _direction; }

		/** Gets the position of a point t units along the ray. */
		Vector3 GetPoint(float t) const
		{
			return Vector3(_origin + (_direction * t));
		}

		/** Gets the position of a point t units along the ray. */
		Vector3 operator*(float t) const
		{
			return GetPoint(t);
		}

		/** Transforms the ray by the given matrix. */
		void Transform(const Matrix4& matrix);

		/**
		* Transforms the ray by the given matrix.
		*
		* @note	Provided matrix must be affine.
		*/
		void TransformAffine(const Matrix4& matrix);

		/** Ray/plane intersection, returns boolean result and distance to intersection point. */
		std::pair<bool, float> Intersects(const Plane& p) const;

		/** Ray/sphere intersection, returns boolean result and distance to nearest intersection point. */
		std::pair<bool, float> Intersects(const Sphere& s) const;

		/** Ray/axis aligned box intersection, returns boolean result and distance to nearest intersection point. */
		std::pair<bool, float> Intersects(const AABox& box) const;

		/**
		* Ray/triangle intersection, returns boolean result and distance to intersection point.
		*
		* @param[in]	a				Triangle first vertex.
		* @param[in]	b				Triangle second vertex.
		* @param[in]	c				Triangle third vertex.
		* @param[in]	normal			The normal of the triangle. Doesn't need to be normalized.
		* @param[in]	positiveSide	(optional) Should intersections with the positive side (normal facing) count.
		* @param[in]	negativeSide	(optional) Should intersections with the negative side (opposite of normal facing) count.
		* @return						Boolean result if intersection happened and distance to intersection point.
		*/
		std::pair<bool, float> Intersects(const Vector3& a, const Vector3& b, const Vector3& c,
			const Vector3& normal, bool positiveSide = true, bool negativeSide = true) const;

	protected:
		Vector3 _origin;
		Vector3 _direction;
	};
}