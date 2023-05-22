#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Multiply(float scalar, const Vector3& v2);

float Clamp(float num, float Min, float Max);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

float Distance(const Vector3& v1, const Vector3& v2);

Vector3 Normalize(const Vector3& V);

Vector3 Slerp(const Vector3& v1, const Vector3& v2,float t);