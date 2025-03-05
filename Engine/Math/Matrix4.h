#pragma once

#include "Core/Type.h"
#include "Vector3.h"


namespace Blue
{
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& other);
		~Matrix4() = default;

		// 메모리 너비(단위 : 바이트).
		static uint32 Stride() { return sizeof(Matrix4); }

		// 이동 변환 행렬.
		static Matrix4 Translation(const Vector3& position);
		static Matrix4 Translation(float x, float y, float z);

		// 회전 변환 행렬.
		static Matrix4 Rotation(const Vector3& rotation);
		static Matrix4 Rotation(float x, float y, float z);
		static Matrix4 RotationX(float angle);
		static Matrix4 RotationY(float angle);
		static Matrix4 RotationZ(float angle);

		// 크기 변환 행렬.
		static Matrix4 Scale(const Vector3& scale);
		static Matrix4 Scale(float scale);
		static Matrix4 Scale(float x, float y, float z);

		// 전치 행렬.
		static Matrix4 Transpose(const Matrix4& target);

		//operator overloading
		Matrix4& operator=(const Matrix4& other);
		Matrix4 operator*(const Matrix4& other);
		Matrix4 operator*=(const Matrix4& other);

		friend Vector3 operator*(const Matrix4& matrix, const Vector3& vector);
		friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix);

		// Degree <-> Radian
		static Matrix4 Identity;
		static constexpr float degreeToRadian = 3.141592f / 180.f;
		static constexpr float radianToDegree = 180.f / 3.141592f;


	private:
		// 공용체.
		union
		{
			struct// 보기 좋으라고.
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			// 공용체 중 메모리 가장 큰 거의 메모리를 공유.
			float elements[4 * 4];
		};
	};
}