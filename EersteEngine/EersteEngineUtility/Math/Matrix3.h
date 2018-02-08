#pragma once

#include "../Prerequisites/PrerequisitesUtility.h"
#include "../Math/Vector3.h"

namespace ee
{
	class EE_UTILITY_EXPORT Matrix3
	{
	private:
		struct EulerAngleOrderData
		{
			int A, B, C;
			float Sign;
		};

	public:
		Matrix3() {}

		Matrix3(EE_ZERO zero)
			:Matrix3(Matrix3::ZERO)
		{ }

		Matrix3(EE_IDENTITY identity)
			:Matrix3(Matrix3::IDENTITY)
		{ }

		Matrix3(const Matrix3& mat)
		{
			memcpy(m, mat.m, 9 * sizeof(float));
		}

		Matrix3(float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}

		/** Construct a matrix from a quaternion. */
		explicit Matrix3(const Quaternion& rotation)
		{
			FromQuaternion(rotation);
		}

		/** Construct a matrix that performs rotation and scale. */
		explicit Matrix3(const Quaternion& rotation, const Vector3& scale)
		{
			FromQuaternion(rotation);

			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
					m[row][col] = scale[row] * m[row][col];
			}
		}

		/** Construct a matrix from an angle/axis pair. */
		explicit Matrix3(const Vector3& axis, const Radian& angle)
		{
			FromAxisAngle(axis, angle);
		}

		/** Construct a matrix from 3 orthonormal local axes. */
		explicit Matrix3(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
		{
			FromAxes(xaxis, yaxis, zaxis);
		}

		/**
		* Construct a matrix from euler angles, YXZ ordering.
		*
		* @see		Matrix3::fromEulerAngles
		*/
		explicit Matrix3(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle)
		{
			FromEulerAngles(xAngle, yAngle, zAngle);
		}

		/**
		* Construct a matrix from euler angles, custom ordering.
		*
		* @see		Matrix3::fromEulerAngles
		*/
		explicit Matrix3(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle, EulerAngleOrder order)
		{
			FromEulerAngles(xAngle, yAngle, zAngle, order);
		}

		/** Swaps the contents of this matrix with another. */
		void Swap(Matrix3& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
		}

		/** Returns a row of the matrix. */
		float* operator[] (UINT32 row) const
		{
			assert(row < 3);

			return (float*)m[row];
		}

		Vector3 GetColumn(UINT32 col) const;
		void SetColumn(UINT32 col, const Vector3& vec);

		Matrix3& operator= (const Matrix3& rhs)
		{
			memcpy(m, rhs.m, 9 * sizeof(float));
			return *this;
		}
		bool operator== (const Matrix3& rhs) const;
		bool operator!= (const Matrix3& rhs) const;

		Matrix3 operator+ (const Matrix3& rhs) const;
		Matrix3 operator- (const Matrix3& rhs) const;
		Matrix3 operator* (const Matrix3& rhs) const;
		Matrix3 operator- () const;
		Matrix3 operator* (float rhs) const;

		friend Matrix3 operator* (float lhs, const Matrix3& rhs);

		/** Transforms the given vector by this matrix and returns the newly transformed vector. */
		Vector3 Transform(const Vector3& vec) const;

		/** Returns a transpose of the matrix (switched columns and rows). */
		Matrix3 Transpose() const;

		/**
		* Calculates an inverse of the matrix if it exists.
		*
		* @param[out]	mat			Resulting matrix inverse.
		* @param[in]	fTolerance 	(optional) Tolerance to use when checking if determinant is zero (or near zero in this case).
		* 							Zero determinant means inverse doesn't exist.
		* @return					True if inverse exists, false otherwise.
		*/
		bool Inverse(Matrix3& mat, float fTolerance = 1e-06f) const;

		/**
		* Calculates an inverse of the matrix if it exists.
		*
		* @param[in]	fTolerance 	(optional) Tolerance to use when checking if determinant is zero (or near zero in this case).
		* 							Zero determinant means inverse doesn't exist.
		*
		* @return					Resulting matrix inverse if it exists, otherwise a zero matrix.
		*/
		Matrix3 Inverse(float fTolerance = 1e-06f) const;

		/** Calculates the matrix determinant. */
		float Determinant() const;

		/**
		* Decompose a Matrix3 to rotation and scale.
		*
		* @note
		* Matrix must consist only of rotation and uniform scale transformations, otherwise accurate results are not
		* guaranteed. Applying non-uniform scale guarantees rotation portion will not be accurate.
		*/
		void Decomposition(Quaternion& rotation, Vector3& scale) const;

		/**
		* Decomposes the matrix into various useful values.
		*
		* @param[out]	matL	Unitary matrix. Columns form orthonormal bases. If your matrix is affine and
		* 						doesn't use non-uniform scaling this matrix will be a conjugate transpose of the rotation part of the matrix.
		* @param[out]	matS	Singular values of the matrix. If your matrix is affine these will be scaling factors of the matrix.
		* @param[out]	matR	Unitary matrix. Columns form orthonormal bases. If your matrix is affine and
		* 						doesn't use non-uniform scaling this matrix will be the rotation part of the matrix.
		*/
		void SingularValueDecomposition(Matrix3& matL, Vector3& matS, Matrix3& matR) const;

		/**
		* Decomposes the matrix into a set of values.
		*
		* @param[out]	matQ	Columns form orthonormal bases. If your matrix is affine and
		* 						doesn't use non-uniform scaling this matrix will be the rotation part of the matrix.
		* @param[out]	vecD	If the matrix is affine these will be scaling factors of the matrix.
		* @param[out]	vecU	If the matrix is affine these will be shear factors of the matrix.
		*/
		void QDUDecomposition(Matrix3& matQ, Vector3& vecD, Vector3& vecU) const;

		/** Gram-Schmidt orthonormalization (applied to columns of rotation matrix) */
		void Orthonormalize();

		/**
		* Converts an orthonormal matrix to axis angle representation.
		*
		* @note	Matrix must be orthonormal.
		*/
		void ToAxisAngle(Vector3& axis, Radian& angle) const;

		/** Creates a rotation matrix from an axis angle representation. */
		void FromAxisAngle(const Vector3& axis, const Radian& angle);

		/**
		* Converts an orthonormal matrix to quaternion representation.
		*
		* @note	Matrix must be orthonormal.
		*/
		void ToQuaternion(Quaternion& quat) const;

		/** Creates a rotation matrix from a quaternion representation. */
		void FromQuaternion(const Quaternion& quat);

		/** Creates a matrix from a three axes. */
		void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

		/**
		* Converts an orthonormal matrix to euler angle (pitch/yaw/roll) representation.
		*
		* @param[in,out]	xAngle	Rotation about x axis. (AKA Pitch)
		* @param[in,out]	yAngle  Rotation about y axis. (AKA Yaw)
		* @param[in,out]	zAngle 	Rotation about z axis. (AKA Roll)
		* @return					True if unique solution was found, false otherwise.
		*
		* @note	Matrix must be orthonormal.
		*/
		bool ToEulerAngles(Radian& xAngle, Radian& yAngle, Radian& zAngle) const;

		/**
		* Creates a rotation matrix from the provided Pitch/Yaw/Roll angles.
		*
		* @param[in]	xAngle	Rotation about x axis. (AKA Pitch)
		* @param[in]	yAngle	Rotation about y axis. (AKA Yaw)
		* @param[in]	zAngle	Rotation about z axis. (AKA Roll)
		*
		* @note	Matrix must be orthonormal.
		* 			Since different values will be produced depending in which order are the rotations applied, this method assumes
		* 			they are applied in YXZ order. If you need a specific order, use the overloaded "fromEulerAngles" method instead.
		*/
		void FromEulerAngles(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle);

		/**
		* Creates a rotation matrix from the provided Pitch/Yaw/Roll angles.
		*
		* @param[in]	xAngle	Rotation about x axis. (AKA Pitch)
		* @param[in]	yAngle	Rotation about y axis. (AKA Yaw)
		* @param[in]	zAngle	Rotation about z axis. (AKA Roll)
		* @param[in]	order 	The order in which rotations will be applied.
		*						Different rotations can be created depending on the order.
		*
		* @note	Matrix must be orthonormal.
		*/
		void FromEulerAngles(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle, EulerAngleOrder order);

		/**
		* Eigensolver, matrix must be symmetric.
		*
		* @note
		* Eigenvectors are vectors which when transformed by the matrix, only change in magnitude, but not in direction.
		* Eigenvalue is that magnitude. In other words you will get the same result whether you multiply the vector by the
		* matrix or by its eigenvalue.
		*/
		void EigenSolveSymmetric(float eigenValues[3], Vector3 eigenVectors[3]) const;

		static const float EPSILON;
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;

	protected:
		friend class Matrix4;

		// Support for eigensolver
		void Tridiagonal(float diag[3], float subDiag[3]);
		bool QLAlgorithm(float diag[3], float subDiag[3]);

		// Support for singular value decomposition
		static const float SVD_EPSILON;
		static const unsigned int SVD_MAX_ITERS;
		static void Bidiagonalize(Matrix3& matA, Matrix3& matL, Matrix3& matR);
		static void GolubKahanStep(Matrix3& matA, Matrix3& matL, Matrix3& matR);

		// Euler angle conversions
		static const EulerAngleOrderData EA_LOOKUP[6];

		float m[3][3];
	};
}