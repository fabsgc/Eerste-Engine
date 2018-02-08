#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"

#include "../Math/Vector3.h"
#include "../Math/Matrix3.h"
#include "../Math/Vector4.h"
#include "../Math/Plane.h"

namespace ee
{
	class EE_UTILITY_EXPORT Matrix4
	{
	private:
		union
		{
			float m[4][4];
			float _m[16];
		};

	public:
		Matrix4()
		{ }

		Matrix4(EE_ZERO zero)
			:Matrix4(Matrix3::ZERO)
		{ }

		Matrix4(EE_IDENTITY identity)
			:Matrix4(Matrix3::IDENTITY)
		{ }

		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		Matrix4(const Matrix4& mat)
		{
			memcpy(_m, mat._m, 16 * sizeof(float));
		}

		/** Creates a 4x4 transformation matrix with a zero translation part from a rotation/scaling 3x3 matrix. */
		explicit Matrix4(const Matrix3& mat3)
		{
			m[0][0] = mat3.m[0][0]; m[0][1] = mat3.m[0][1]; m[0][2] = mat3.m[0][2]; m[0][3] = 0.0f;
			m[1][0] = mat3.m[1][0]; m[1][1] = mat3.m[1][1]; m[1][2] = mat3.m[1][2]; m[1][3] = 0.0f;
			m[2][0] = mat3.m[2][0]; m[2][1] = mat3.m[2][1]; m[2][2] = mat3.m[2][2]; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		/** Swaps the contents of this matrix with another. */
		void Swap(Matrix4& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[0][3], other.m[0][3]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[1][3], other.m[1][3]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
			std::swap(m[2][3], other.m[2][3]);
			std::swap(m[3][0], other.m[3][0]);
			std::swap(m[3][1], other.m[3][1]);
			std::swap(m[3][2], other.m[3][2]);
			std::swap(m[3][3], other.m[3][3]);
		}

		/** Returns a row of the matrix. */
		Vector4& operator[] (UINT32 row)
		{
			assert(row < 4);

			return *(Vector4*)m[row];
		}

		/** Returns a row of the matrix. */
		const Vector4& operator[] (UINT32 row) const
		{
			assert(row < 4);

			return *(Vector4*)m[row];
		}

		Matrix4 operator* (const Matrix4 &rhs) const
		{
			Matrix4 r;

			r.m[0][0] = m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0] + m[0][2] * rhs.m[2][0] + m[0][3] * rhs.m[3][0];
			r.m[0][1] = m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1] + m[0][2] * rhs.m[2][1] + m[0][3] * rhs.m[3][1];
			r.m[0][2] = m[0][0] * rhs.m[0][2] + m[0][1] * rhs.m[1][2] + m[0][2] * rhs.m[2][2] + m[0][3] * rhs.m[3][2];
			r.m[0][3] = m[0][0] * rhs.m[0][3] + m[0][1] * rhs.m[1][3] + m[0][2] * rhs.m[2][3] + m[0][3] * rhs.m[3][3];

			r.m[1][0] = m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0] + m[1][2] * rhs.m[2][0] + m[1][3] * rhs.m[3][0];
			r.m[1][1] = m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1] + m[1][2] * rhs.m[2][1] + m[1][3] * rhs.m[3][1];
			r.m[1][2] = m[1][0] * rhs.m[0][2] + m[1][1] * rhs.m[1][2] + m[1][2] * rhs.m[2][2] + m[1][3] * rhs.m[3][2];
			r.m[1][3] = m[1][0] * rhs.m[0][3] + m[1][1] * rhs.m[1][3] + m[1][2] * rhs.m[2][3] + m[1][3] * rhs.m[3][3];

			r.m[2][0] = m[2][0] * rhs.m[0][0] + m[2][1] * rhs.m[1][0] + m[2][2] * rhs.m[2][0] + m[2][3] * rhs.m[3][0];
			r.m[2][1] = m[2][0] * rhs.m[0][1] + m[2][1] * rhs.m[1][1] + m[2][2] * rhs.m[2][1] + m[2][3] * rhs.m[3][1];
			r.m[2][2] = m[2][0] * rhs.m[0][2] + m[2][1] * rhs.m[1][2] + m[2][2] * rhs.m[2][2] + m[2][3] * rhs.m[3][2];
			r.m[2][3] = m[2][0] * rhs.m[0][3] + m[2][1] * rhs.m[1][3] + m[2][2] * rhs.m[2][3] + m[2][3] * rhs.m[3][3];

			r.m[3][0] = m[3][0] * rhs.m[0][0] + m[3][1] * rhs.m[1][0] + m[3][2] * rhs.m[2][0] + m[3][3] * rhs.m[3][0];
			r.m[3][1] = m[3][0] * rhs.m[0][1] + m[3][1] * rhs.m[1][1] + m[3][2] * rhs.m[2][1] + m[3][3] * rhs.m[3][1];
			r.m[3][2] = m[3][0] * rhs.m[0][2] + m[3][1] * rhs.m[1][2] + m[3][2] * rhs.m[2][2] + m[3][3] * rhs.m[3][2];
			r.m[3][3] = m[3][0] * rhs.m[0][3] + m[3][1] * rhs.m[1][3] + m[3][2] * rhs.m[2][3] + m[3][3] * rhs.m[3][3];

			return r;
		}

		Matrix4 operator+ (const Matrix4 &rhs) const
		{
			Matrix4 r;

			r.m[0][0] = m[0][0] + rhs.m[0][0];
			r.m[0][1] = m[0][1] + rhs.m[0][1];
			r.m[0][2] = m[0][2] + rhs.m[0][2];
			r.m[0][3] = m[0][3] + rhs.m[0][3];

			r.m[1][0] = m[1][0] + rhs.m[1][0];
			r.m[1][1] = m[1][1] + rhs.m[1][1];
			r.m[1][2] = m[1][2] + rhs.m[1][2];
			r.m[1][3] = m[1][3] + rhs.m[1][3];

			r.m[2][0] = m[2][0] + rhs.m[2][0];
			r.m[2][1] = m[2][1] + rhs.m[2][1];
			r.m[2][2] = m[2][2] + rhs.m[2][2];
			r.m[2][3] = m[2][3] + rhs.m[2][3];

			r.m[3][0] = m[3][0] + rhs.m[3][0];
			r.m[3][1] = m[3][1] + rhs.m[3][1];
			r.m[3][2] = m[3][2] + rhs.m[3][2];
			r.m[3][3] = m[3][3] + rhs.m[3][3];

			return r;
		}

		Matrix4 operator- (const Matrix4 &rhs) const
		{
			Matrix4 r;
			r.m[0][0] = m[0][0] - rhs.m[0][0];
			r.m[0][1] = m[0][1] - rhs.m[0][1];
			r.m[0][2] = m[0][2] - rhs.m[0][2];
			r.m[0][3] = m[0][3] - rhs.m[0][3];

			r.m[1][0] = m[1][0] - rhs.m[1][0];
			r.m[1][1] = m[1][1] - rhs.m[1][1];
			r.m[1][2] = m[1][2] - rhs.m[1][2];
			r.m[1][3] = m[1][3] - rhs.m[1][3];

			r.m[2][0] = m[2][0] - rhs.m[2][0];
			r.m[2][1] = m[2][1] - rhs.m[2][1];
			r.m[2][2] = m[2][2] - rhs.m[2][2];
			r.m[2][3] = m[2][3] - rhs.m[2][3];

			r.m[3][0] = m[3][0] - rhs.m[3][0];
			r.m[3][1] = m[3][1] - rhs.m[3][1];
			r.m[3][2] = m[3][2] - rhs.m[3][2];
			r.m[3][3] = m[3][3] - rhs.m[3][3];

			return r;
		}

		inline bool operator== (const Matrix4& rhs) const
		{
			if (m[0][0] != rhs.m[0][0] || m[0][1] != rhs.m[0][1] || m[0][2] != rhs.m[0][2] || m[0][3] != rhs.m[0][3] ||
				m[1][0] != rhs.m[1][0] || m[1][1] != rhs.m[1][1] || m[1][2] != rhs.m[1][2] || m[1][3] != rhs.m[1][3] ||
				m[2][0] != rhs.m[2][0] || m[2][1] != rhs.m[2][1] || m[2][2] != rhs.m[2][2] || m[2][3] != rhs.m[2][3] ||
				m[3][0] != rhs.m[3][0] || m[3][1] != rhs.m[3][1] || m[3][2] != rhs.m[3][2] || m[3][3] != rhs.m[3][3])
			{
				return false;
			}

			return true;
		}

		inline bool operator!= (const Matrix4& rhs) const
		{
			return !operator==(rhs);
		}

		Matrix4 operator*(float rhs) const
		{
			return Matrix4(rhs*m[0][0], rhs*m[0][1], rhs*m[0][2], rhs*m[0][3],
				rhs*m[1][0], rhs*m[1][1], rhs*m[1][2], rhs*m[1][3],
				rhs*m[2][0], rhs*m[2][1], rhs*m[2][2], rhs*m[2][3],
				rhs*m[3][0], rhs*m[3][1], rhs*m[3][2], rhs*m[3][3]);
		}

		/** Returns the specified column of the matrix, ignoring the last row. */
		Vector3 GetColumn(UINT32 col) const
		{
			assert(col < 4);

			return Vector3(m[0][col], m[1][col], m[2][col]);
		}

		/** Returns the specified column of the matrix. */
		Vector4 GetColumn4D(UINT32 col) const
		{
			assert(col < 4);

			return Vector4(m[0][col], m[1][col], m[2][col], m[3][col]);
		}

		/** Returns a transpose of the matrix (switched columns and rows). */
		Matrix4 Transpose() const
		{
			return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
				m[0][1], m[1][1], m[2][1], m[3][1],
				m[0][2], m[1][2], m[2][2], m[3][2],
				m[0][3], m[1][3], m[2][3], m[3][3]);
		}

		/** Assigns the vector to a column of the matrix. */
		void SetColumn(UINT32 idx, const Vector4& column)
		{
			m[0][idx] = column.x;
			m[1][idx] = column.y;
			m[2][idx] = column.z;
			m[3][idx] = column.w;
		}

		/** Assigns the vector to a row of the matrix. */
		void SetRow(UINT32 idx, const Vector4& column)
		{
			m[idx][0] = column.x;
			m[idx][1] = column.y;
			m[idx][2] = column.z;
			m[idx][3] = column.w;
		}

		/** Extracts the rotation/scaling part of the matrix as a 3x3 matrix. */
		void Extract3x3Matrix(Matrix3& m3x3) const
		{
			m3x3.m[0][0] = m[0][0];
			m3x3.m[0][1] = m[0][1];
			m3x3.m[0][2] = m[0][2];
			m3x3.m[1][0] = m[1][0];
			m3x3.m[1][1] = m[1][1];
			m3x3.m[1][2] = m[1][2];
			m3x3.m[2][0] = m[2][0];
			m3x3.m[2][1] = m[2][1];
			m3x3.m[2][2] = m[2][2];
		}

		/** Calculates the adjoint of the matrix. */
		Matrix4 Adjoint() const;

		/** Calculates the determinant of the matrix. */
		float Determinant() const;

		/** Calculates the determinant of the 3x3 sub-matrix. */
		float Determinant3x3() const;

		/** Calculates the inverse of the matrix. */
		Matrix4 Inverse() const;

		/**
		* Creates a matrix from translation, rotation and scale.
		* @note	The transformation are applied in scale->rotation->translation order.
		*/
		void SetTRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		/**
		* Creates a matrix from inverse translation, rotation and scale.
		* @note	This is cheaper than setTRS() and then performing inverse().
		*/
		void SetInverseTRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		/**
		* Decompose a Matrix4 to translation, rotation and scale.
		*
		* @note
		* Matrix must consist only of translation, rotation and uniform scale transformations,
		* otherwise accurate results are not guaranteed. Applying non-uniform scale guarantees
		* results will not be accurate.
		*/
		void Decomposition(Vector3& position, Quaternion& rotation, Vector3& scale) const;

		/** Extracts the translation (position) part of the matrix. */
		Vector3 GetTranslation() const { return Vector3(m[0][3], m[1][3], m[2][3]); }

		/**
		* Check whether or not the matrix is affine matrix.
		* @note	An affine matrix is a 4x4 matrix with row 3 equal to (0, 0, 0, 1), meaning no projective coefficients.
		*/
		bool IsAffine() const
		{
			return m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1;
		}

		/**
		* Returns the inverse of the affine matrix.
		* @note	Matrix must be affine.
		*/
		Matrix4 InverseAffine() const;

		/**
		* Concatenate two affine matrices.
		* @note	Both matrices must be affine.
		*/
		Matrix4 ConcatenateAffine(const Matrix4 &other) const
		{
			EE_ASSERT_ERROR_SHORT(IsAffine() && other.IsAffine());

			return Matrix4(
				m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0],
				m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1],
				m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2],
				m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] + m[0][2] * other.m[2][3] + m[0][3],

				m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0],
				m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1],
				m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2],
				m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] + m[1][2] * other.m[2][3] + m[1][3],

				m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0],
				m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1],
				m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2],
				m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] + m[2][2] * other.m[2][3] + m[2][3],

				0, 0, 0, 1);
		}

		/**
		* Transform a plane by this matrix.
		* @note	Matrix must be affine.
		*/
		Plane MultiplyAffine(const Plane& p) const
		{
			Vector4 localNormal(p.normal.x, p.normal.y, p.normal.z, 0.0f);
			Vector4 localPoint = localNormal * p.d;
			localPoint.w = 1.0f;

			Matrix4 itMat = Inverse().Transpose();
			Vector4 worldNormal = itMat.MultiplyAffine(localNormal);
			Vector4 worldPoint = MultiplyAffine(localPoint);

			float d = worldNormal.Dot(worldPoint);

			return Plane(worldNormal.x, worldNormal.y, worldNormal.z, d);
		}

		/**
		* Transform a 3D point by this matrix.
		* @note	Matrix must be affine, if it is not use multiply() method.
		*/
		Vector3 MultiplyAffine(const Vector3& v) const
		{
			return Vector3(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]);
		}

		/**
		* Transform a 4D vector by this matrix.
		* @note	Matrix must be affine, if it is not use multiply() method.
		*/
		Vector4 MultiplyAffine(const Vector4& v) const
		{
			return Vector4(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
				v.w);
		}

		/** Transform a 3D direction by this matrix. */
		Vector3 MultiplyDirection(const Vector3& v) const
		{
			return Vector3(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
		}

		/**
		* Transform a 3D point by this matrix.
		*
		* @note
		* w component of the vector is assumed to be 1. After transformation all components
		* are projected back so that w remains 1.
		* @note
		* If your matrix doesn't contain projection components use multiplyAffine() method as it is faster.
		*/
		Vector3 Multiply(const Vector3& v) const
		{
			Vector3 r;

			float fInvW = 1.0f / (m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3]);

			r.x = (m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3]) * fInvW;
			r.y = (m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3]) * fInvW;
			r.z = (m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]) * fInvW;

			return r;
		}

		/**
		* Transform a 4D vector by this matrix.
		* @note	If your matrix doesn't contain projection components use multiplyAffine() method as it is faster.
		*/
		Vector4 Multiply(const Vector4& v) const
		{
			return Vector4(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
				m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
			);
		}

		/** Creates a view matrix and applies optional reflection. */
		void MakeView(const Vector3& position, const Quaternion& orientation);

		/**
		* Creates an ortographic projection matrix that scales the part of the view bounded by @p left, @p right,
		* @p top and @p bottom into [-1, 1] range. If @p far is non-zero the matrix will also transform the depth into
		* [-1, 1] range, otherwise it will leave it as-is.
		*/
		void MakeProjectionOrtho(float left, float right, float top, float bottom, float _near, float _far);

		/** Creates a 4x4 transformation matrix that performs translation. */
		static Matrix4 Translation(const Vector3& translation);

		/** Creates a 4x4 transformation matrix that performs scaling. */
		static Matrix4 Scaling(const Vector3& scale);

		/** Creates a 4x4 transformation matrix that performs uniform scaling. */
		static Matrix4 Scaling(float scale);

		/** Creates a 4x4 transformation matrix that performs rotation. */
		static Matrix4 Rotation(const Quaternion& rotation);

		/**
		* Creates a 4x4 perspective projection matrix.
		*
		* @param[in]	horzFOV		Horizontal field of view.
		* @param[in]	aspect		Aspect ratio. Determines the vertical field of view.
		* @param[in]	near		Distance to the near plane.
		* @param[in]	far			Distance to the far plane.
		* @param[in]	positiveZ	If true the matrix will project geometry as if its looking along the positive Z axis.
		*							Otherwise it projects along the negative Z axis (default).
		*/
		static Matrix4 ProjectionPerspective(const Degree& horzFOV, float aspect, float _near, float _far,
			bool positiveZ = false);

		/** @copydoc makeProjectionOrtho() */
		static Matrix4 ProjectionOrthographic(float left, float right, float top, float bottom, float _near, float _far);

		/** Creates a view matrix. */
		static Matrix4 View(const Vector3& position, const Quaternion& orientation);

		/**
		* Creates a matrix from translation, rotation and scale.
		* @note	The transformation are applied in scale->rotation->translation order.
		*/
		static Matrix4 TRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		/**
		* Creates a matrix from inverse translation, rotation and scale.
		* @note	This is cheaper than setTRS() and then performing inverse().
		*/
		static Matrix4 InverseTRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		static const Matrix4 ZERO;
		static const Matrix4 IDENTITY;
	};
}
