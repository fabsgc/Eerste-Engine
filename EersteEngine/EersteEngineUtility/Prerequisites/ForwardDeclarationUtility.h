#pragma once

namespace ee
{
	enum class EulerAngleOrder
	{
		XYZ,
		XZY,
		YXZ,
		YZX,
		ZXY,
		ZYX
	};

	/** Enum used for object construction specifying the object should be zero initializes. */
	enum EE_ZERO { EeZero };

	/** Enum used for matrix/quaternion constructor specifying it should be initialized with an identity value. */
	enum EE_IDENTITY { EeIdentity };

	class Degree;
	class Radian;
	class Math;
	class Vector2;
	class Vector3;
	class Vector4;
	class Vector2I;
	class Quaternion;
	class Matrix3;
	class Matrix4;
	class Rect2;
	class Rect2I;
	class Plane;
	class Sphere;
	class AABox;
	class Ray;
	class Bounds;
}