#pragma once
#define EPSILON				0.001f

class Vector2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};
		float v[2];
	};

public:

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);
	Vector2(Vector2&& other);
	~Vector2();

	Vector2& operator=(const Vector2& other);
	Vector2& operator=(Vector2&& other) noexcept;

	float& operator[](size_t idx);
	float  operator[](size_t idx) const;
	float* operator&();

};

class Vector3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float v[3];
	};

public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);
	Vector3(Vector3&& other);
	~Vector3();

	Vector3& operator=(const Vector3& other);
	Vector3& operator=(Vector3&& other) noexcept;

	float& operator[](size_t idx);
	float  operator[](size_t idx) const;
	float* operator&();
};

class Vector4
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};

public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& other);
	Vector4(Vector4&& other);
	~Vector4();

	Vector4& operator=(const Vector4& other);
	Vector4& operator=(Vector4&& other) noexcept;

	float& operator[](size_t idx);
	float  operator[](size_t idx) const;
	float* operator&();
};

class Matrix4x4
{
public:
	union
	{
		struct
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};
		Vector4 v[4];
	};

public:
	Matrix4x4();
	Matrix4x4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	Matrix4x4(const Matrix4x4& other);
	Matrix4x4(Matrix4x4&& other);
	~Matrix4x4();

	Matrix4x4& operator=(const Matrix4x4& other);
	Matrix4x4& operator=(Matrix4x4&& other) noexcept;

	Vector4& operator[](size_t idx);
	Vector4  operator[](size_t idx) const;
	float *operator&();
};

/* OPERATIONS ------------------------------------------------------------------------------------------------------ */

inline bool isZero(float fNum)
{
	return fabsf(fNum) < EPSILON;
}

inline bool areEqual(float fLhs, float fRhs)
{
	return isZero(fLhs - fRhs);
}

namespace V3
{
	inline Vector3 add(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3
		(
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z
		);
	}

	inline Vector3 subtract(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3
		(
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z
		);
	}

	inline float dot(const Vector3& lhs, const Vector3& rhs)
	{
		return
			(lhs.x * rhs.x) +
			(lhs.y * rhs.y) +
			(lhs.z * rhs.z);
	}

	inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 v3Result;
		v3Result.x = lhs.y * rhs.z - lhs.z * rhs.y;
		v3Result.y = lhs.z * rhs.x - lhs.x * rhs.z;
		v3Result.z = lhs.x * rhs.y - lhs.y * rhs.x;
		return v3Result;
	}

	inline float size(const Vector3& v3Vector)
	{
		return sqrtf(V3::dot(v3Vector, v3Vector));
	}

	inline Vector3 normalize(const Vector3& v3Vector)
	{
		Vector3 v3Result;
		float fSize = size(v3Vector);
		v3Result.x = v3Vector.x / fSize;
		v3Result.y = v3Vector.y / fSize;
		v3Result.z = v3Vector.z / fSize;

		return v3Result;
	}
}

namespace V4
{
	inline Vector4 mult(const Matrix4x4& lMatrix, const Vector4& rColumnVector)
	{
		Vector4 v4Result(0.f, 0.f, 0.f, 0.f);
		for (size_t i = 0; i < 4; ++i)
			for (size_t j = 0; j < 4; ++j)
			{
				float f1 = lMatrix[i][j];
				float f2 = rColumnVector[j];
				v4Result[i] += f1 * f2;
			}

		return v4Result;
	}

	inline Vector4 mult(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 v4Result;
		v4Result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
		v4Result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
		v4Result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
		v4Result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
		return v4Result;
	}

	inline Vector4 conj(const Vector4& q)
	{
		return Vector4(-q.x, -q.y, -q.z, q.w);
	}
}
