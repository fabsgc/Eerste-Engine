#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"

namespace ee
{
	/** Axis aligned box represented by minimum and maximum point. */
	class EE_UTILITY_EXPORT AABox
	{
	public:
		/** Different corners of a box. */
		/*
		1-----2
		/|    /|
		/ |   / |
		5-----4  |
		|  0--|--3
		| /   | /
		|/    |/
		6-----7
		*/
		enum Corner
		{
			FAR_LEFT_BOTTOM = 0,
			FAR_LEFT_TOP = 1,
			FAR_RIGHT_TOP = 2,
			FAR_RIGHT_BOTTOM = 3,
			NEAR_RIGHT_BOTTOM = 7,
			NEAR_LEFT_BOTTOM = 6,
			NEAR_LEFT_TOP = 5,
			NEAR_RIGHT_TOP = 4
		};

		AABox();
		AABox(const AABox& copy);
		AABox(const Vector3& min, const Vector3& max);

		AABox& operator=(const AABox& rhs);

		~AABox() { }

		/** Gets the corner of the box with minimum values (opposite to maximum corner). */
		const Vector3& GetMin() const { return _minimum; }

		/** Gets the corner of the box with maximum values (opposite to minimum corner). */
		const Vector3& GetMax() const { return _maximum; }

		/** Sets the corner of the box with minimum values (opposite to maximum corner). */
		void SetMin(const Vector3& vec) { _minimum = vec; }

		/** Sets the corner of the box with maximum values (opposite to minimum corner). */
		void SetMax(const Vector3& vec) { _maximum = vec; }

		/** Sets the minimum and maximum corners. */
		void SetExtents(const Vector3& min, const Vector3& max);

		/** Scales the box around the center by multiplying its extents with the provided scale. */
		void Scale(const Vector3& s);

		/** Returns the coordinates of a specific corner. */
		Vector3 GetCorner(Corner cornerToGet) const;

		/** Merges the two boxes, creating a new bounding box that encapsulates them both. */
		void Merge(const AABox& rhs);

		/** Expands the bounding box so it includes the provided point. */
		void Merge(const Vector3& point);

		/**
		* Transforms the bounding box by the given matrix.
		*
		* @note
		* As the resulting box will no longer be axis aligned, an axis align box
		* is instead created by encompassing the transformed oriented bounding box.
		* Retrieving the value as an actual OBB would provide a tighter fit.
		*/
		void Transform(const Matrix4& matrix);

		/**
		* Transforms the bounding box by the given matrix.
		*
		* @note
		* As the resulting box will no longer be axis aligned, an axis align box
		* is instead created by encompassing the transformed oriented bounding box.
		* Retrieving the value as an actual OBB would provide a tighter fit.
		*
		* @note
		* Provided matrix must be affine.
		*/
		void TransformAffine(const Matrix4& matrix);

		/** Returns true if this and the provided box intersect. */
		bool Intersects(const AABox& b2) const;

		/** Returns true if the sphere intersects the bounding box. */
		bool Intersects(const Sphere& s) const;

		/** Returns true if the plane intersects the bounding box. */
		bool Intersects(const Plane& p) const;

		/** Ray / box intersection, returns a boolean result and nearest distance to intersection. */
		std::pair<bool, float> Intersects(const Ray& ray) const;

		/** Ray / box intersection, returns boolean result and near and far intersection distance. */
		bool Intersects(const Ray& ray, float& d1, float& d2) const;

		/** Center of the box. */
		Vector3 GetCenter() const;

		/** Size of the box (difference between minimum and maximum corners) */
		Vector3 GetSize() const;

		/** Extents of the box (distance from center to one of the corners) */
		Vector3 GetHalfSize() const;

		/** Radius of a sphere that fully encompasses the box. */
		float GetRadius() const;

		/** Size of the volume in the box. */
		float GetVolume() const;

		/** Returns true if the provided point is inside the bounding box. */
		bool Contains(const Vector3& v) const;

		/** Returns true if the provided bounding box is completely inside the bounding box. */
		bool Contains(const AABox& other) const;

		bool operator== (const AABox& rhs) const;
		bool operator!= (const AABox& rhs) const;

		static const AABox BOX_EMPTY;
		static const AABox UNIT_BOX;

		/**
		* Indices that can be used for rendering a box constructed from 8 corner vertices, using AABox::Corner for
		* mapping.
		*/
		static const UINT32 CUBE_INDICES[36];

	protected:
		Vector3 _minimum;
		Vector3 _maximum;
	};
}
