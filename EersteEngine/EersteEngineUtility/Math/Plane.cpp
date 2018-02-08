#include "../Math/Plane.h"
#include "../Math/Matrix3.h"
#include "../Math/AABox.h"
#include "../Math/Sphere.h"
#include "../Math/Ray.h"
#include "../Math/Math.h"

namespace ee
{
	Plane::Plane()
		:normal(), d(0.0f)
	{ }

	Plane::Plane(const Plane& copy)
		: normal(copy.normal), d(copy.d)
	{ }

	Plane::Plane(const Vector3& normal, float d)
		: normal(normal), d(d)
	{ }

	Plane::Plane(float a, float b, float c, float _d)
		: normal(a, b, c), d(_d)
	{ }

	Plane::Plane(const Vector3& normal, const Vector3& point)
		: normal(normal), d(normal.Dot(point))
	{ }

	Plane::Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2)
	{
		Vector3 kEdge1 = point1 - point0;
		Vector3 kEdge2 = point2 - point0;
		normal = kEdge1.Cross(kEdge2);
		normal.Normalize();
		d = normal.Dot(point0);
	}

	float Plane::GetDistance(const Vector3& point) const
	{
		return normal.Dot(point) - d;
	}

	Plane::Side Plane::GetSide(const Vector3& point) const
	{
		float dist = GetDistance(point);

		if (dist < 0.0f)
			return Plane::NEGATIVE_SIDE;

		if (dist > 0.0f)
			return Plane::POSITIVE_SIDE;

		return Plane::NO_SIDE;
	}

	Plane::Side Plane::GetSide(const AABox& box) const
	{
		// Calculate the distance between box centre and the plane
		float dist = GetDistance(box.GetCenter());

		// Calculate the maximize allows absolute distance for
		// the distance between box centre and plane
		Vector3 halfSize = box.GetHalfSize();
		float maxAbsDist = Math::Abs(normal.x * halfSize.x) + Math::Abs(normal.y * halfSize.y) + Math::Abs(normal.z * halfSize.z);

		if (dist < -maxAbsDist)
			return Plane::NEGATIVE_SIDE;

		if (dist > +maxAbsDist)
			return Plane::POSITIVE_SIDE;

		return Plane::BOTH_SIDE;
	}

	Plane::Side Plane::GetSide(const Sphere& sphere) const
	{
		// Calculate the distance between box centre and the plane
		float dist = GetDistance(sphere.GetCenter());
		float radius = sphere.GetRadius();

		if (dist < -radius)
			return Plane::NEGATIVE_SIDE;

		if (dist > +radius)
			return Plane::POSITIVE_SIDE;

		return Plane::BOTH_SIDE;
	}

	Vector3 Plane::ProjectVector(const Vector3& point) const
	{
		// We know plane normal is unit length, so use simple method
		Matrix3 xform;
		xform[0][0] = 1.0f - normal.x * normal.x;
		xform[0][1] = -normal.x * normal.y;
		xform[0][2] = -normal.x * normal.z;
		xform[1][0] = -normal.y * normal.x;
		xform[1][1] = 1.0f - normal.y * normal.y;
		xform[1][2] = -normal.y * normal.z;
		xform[2][0] = -normal.z * normal.x;
		xform[2][1] = -normal.z * normal.y;
		xform[2][2] = 1.0f - normal.z * normal.z;
		return xform.Transform(point);

	}

	float Plane::Normalize()
	{
		float fLength = normal.Length();

		// Will also work for zero-sized vectors, but will change nothing
		if (fLength > 1e-08f)
		{
			float fInvLength = 1.0f / fLength;
			normal *= fInvLength;
			d *= fInvLength;
		}

		return fLength;
	}

	bool Plane::Intersects(const AABox& box) const
	{
		return box.Intersects(*this);
	}

	bool Plane::Intersects(const Sphere& sphere) const
	{
		return sphere.Intersects(*this);
	}

	std::pair<bool, float> Plane::Intersects(const Ray& ray) const
	{
		float denom = normal.Dot(ray.GetDirection());
		if (Math::Abs(denom) < std::numeric_limits<float>::epsilon())
		{
			// Parallel
			return std::pair<bool, float>(false, 0.0f);
		}
		else
		{
			float nom = normal.Dot(ray.GetOrigin()) - d;
			float t = -(nom / denom);
			return std::pair<bool, float>(t >= 0.0f, t);
		}
	}
}
