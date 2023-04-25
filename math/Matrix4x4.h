#pragma once
/// <summary>
/// 4x4行列
/// </summary>
///
#include "Vector3.h"
#include <Math.h>
#include <cmath>
struct Matrix4x4 final {
	float m[4][4];
};

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 Transpose(const Matrix4x4& m);

Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

float AMatrixMuliply4(Matrix4x4 m, int num);

float AMatrixMuliply3(Matrix4x4 m, int num);

float MatrixAbs(Matrix4x4 m);

Matrix4x4 MakeRotateXmatrix(float radian);

Matrix4x4 MakeRotateYmatrix(float radian);

Matrix4x4 MakeRotateZmatrix(float radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale,const Vector3& rot,const Vector3& translate);

Vector3 TransforNormal(const Vector3& v, const Matrix4x4& m);