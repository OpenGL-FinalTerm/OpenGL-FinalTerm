#include "stdafx.h"
#include "LinearMath.h"

/* VECTOR 2 ------------------------------------------------------------------------------------------------------ */

Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(float x_, float y_)
{
	x = x_;
	y = y_;
}

Vector2::Vector2(const Vector2 & other)
{
	x = other.x;
	y = other.y;
}

Vector2::Vector2(Vector2 && other)
{
	x = std::move(other.x);
	y = std::move(other.y);
}

Vector2::~Vector2()
{
}

Vector2 & Vector2::operator=(const Vector2 & other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Vector2 & Vector2::operator=(Vector2 && other) noexcept
{
	x = std::move(other.x);
	y = std::move(other.y);
	return *this;
}

float & Vector2::operator[](size_t idx)
{
	assert(idx >= 0 && idx < 2);
	return v[idx];
}

float Vector2::operator[](size_t idx) const
{
	assert(idx >= 0 && idx < 2);
	return v[idx];
}

float * Vector2::operator&()
{
	return &v[0];
}


/* VECTOR 3 ------------------------------------------------------------------------------------------------------ */

Vector3::Vector3()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

Vector3::Vector3(const Vector3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3::Vector3(Vector3 && other)
{
	x = std::move(other.x);
	y = std::move(other.y);
	z = std::move(other.z);
}

Vector3::~Vector3()
{
}

Vector3 & Vector3::operator=(const Vector3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector3 & Vector3::operator=(Vector3 && other) noexcept
{
	x = std::move(other.x);
	y = std::move(other.y);
	z = std::move(other.z);
	return *this;
}

float & Vector3::operator[](size_t idx)
{
	assert(idx >= 0 && idx < 3);
	return v[idx];
}

float Vector3::operator[](size_t idx) const
{
	assert(idx >= 0 && idx < 3);
	return v[idx];
}

float * Vector3::operator&()
{
	return &v[0];
}


/* VECTOR 4 ------------------------------------------------------------------------------------------------------ */

Vector4::Vector4()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
}

Vector4::Vector4(float x_, float y_, float z_, float w_)
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

Vector4::Vector4(const Vector4 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.z;
}

Vector4::Vector4(Vector4 && other)
{
	x = std::move(other.x);
	y = std::move(other.y);
	z = std::move(other.z);
	w = std::move(other.w);
}

Vector4::~Vector4()
{
}

Vector4 & Vector4::operator=(const Vector4 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

Vector4 & Vector4::operator=(Vector4 && other) noexcept
{
	x = std::move(other.x);
	y = std::move(other.y);
	z = std::move(other.z);
	w = std::move(other.w);
	return *this;
}

float & Vector4::operator[](size_t idx)
{
	assert(idx >= 0 && idx < 4);
	return v[idx];
}

float Vector4::operator[](size_t idx) const
{
	assert(idx >= 0 && idx < 4);
	return v[idx];
}

float * Vector4::operator&()
{
	return &v[0];
}


/* MATRIX 4x4 ------------------------------------------------------------------------------------------------------ */

Matrix4x4::Matrix4x4()
{
	m11 = 0.f;	m12 = 0.f;	m13 = 0.f;	m14 = 0.f;
	m21 = 0.f;	m22 = 0.f;	m23 = 0.f;	m24 = 0.f;
	m31 = 0.f;	m32 = 0.f;	m33 = 0.f;	m34 = 0.f;
	m41 = 0.f;	m42 = 0.f;	m43 = 0.f;	m44 = 0.f;
}

Matrix4x4::Matrix4x4(
	float m11_, float m12_, float m13_, float m14_,
	float m21_, float m22_, float m23_, float m24_,
	float m31_, float m32_, float m33_, float m34_,
	float m41_, float m42_, float m43_, float m44_)
{
	m11 = m11_;	m12 = m12_;	m13 = m13_;	m14 = m14_;
	m21 = m21_;	m22 = m22_;	m23 = m23_;	m24 = m24_;
	m31 = m31_;	m32 = m32_;	m33 = m33_;	m34 = m34_;
	m41 = m41_;	m42 = m42_;	m43 = m43_;	m44 = m44_;
}


Matrix4x4::Matrix4x4(const Matrix4x4 & other)
{
	for (size_t i = 0; i < 4; ++i)
	{
		v[i].x = other[i].x;
		v[i].y = other[i].y;
		v[i].z = other[i].z;
		v[i].w = other[i].w;
	}
}

Matrix4x4::Matrix4x4(Matrix4x4 && other)
{
	for (size_t i = 0; i < 4; ++i)
	{
		v[i].x = std::move(other[i].x);
		v[i].y = std::move(other[i].y);
		v[i].z = std::move(other[i].z);
		v[i].w = std::move(other[i].w);
	}
}

Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & other)
{
	for (size_t i = 0; i < 4; ++i)
	{
		v[i].x = other[i].x;
		v[i].y = other[i].y;
		v[i].z = other[i].z;
		v[i].w = other[i].w;
	}
	return *this;
}

Matrix4x4 & Matrix4x4::operator=(Matrix4x4 && other) noexcept
{
	for (size_t i = 0; i < 4; ++i)
	{
		v[i].x = std::move(other[i].x);
		v[i].y = std::move(other[i].y);
		v[i].z = std::move(other[i].z);
		v[i].w = std::move(other[i].w);
	}
	return *this;
}

Vector4 & Matrix4x4::operator[](size_t idx)
{
	assert(idx >= 0 && idx < 4);
	return v[idx];
}

Vector4 Matrix4x4::operator[](size_t idx) const
{
	assert(idx >= 0 && idx < 4);
	return v[idx];
}

float* Matrix4x4::operator&()
{
	return &v[0][0];
}

