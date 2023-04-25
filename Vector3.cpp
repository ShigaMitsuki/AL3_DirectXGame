#include "Vector3.h"
#include <Math.h>

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 AnserV = {0.0f, 0.0f, 0.0f};

	AnserV.x = v1.x + v2.x;
	AnserV.y = v1.y + v2.y;
	AnserV.z = v1.z + v2.z;

	return AnserV;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 AnserV = {0.0f, 0.0f, 0.0f};

	AnserV.x = v1.x - v2.x;
	AnserV.y = v1.y - v2.y;
	AnserV.z = v1.z - v2.z;

	return AnserV;
}

Vector3 Multiply(float scalar, const Vector3& V) {
	Vector3 AnserV = {0.0f, 0.0f, 0.0f};

	AnserV.x = scalar * V.x;
	AnserV.y = scalar * V.y;
	AnserV.z = scalar * V.z;

	return AnserV;
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float Anser = 0.0f;

	Anser = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return Anser;
}

float Length(const Vector3& v) {
	float Anser = 0.0f;
	Anser = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return Anser;
}

Vector3 Normalize(const Vector3& V) {
	Vector3 AnserV = {0.0f, 0.0f, 0.0f};

	AnserV.x = V.x / sqrtf(V.x * V.x + V.y * V.y + V.z * V.z);
	AnserV.y = V.y / sqrtf(V.x * V.x + V.y * V.y + V.z * V.z);
	AnserV.z = V.z / sqrtf(V.x * V.x + V.y * V.y + V.z * V.z);

	return AnserV;
}
