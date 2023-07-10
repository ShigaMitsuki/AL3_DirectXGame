#include "Matrix4x4.h"
#include <assert.h>

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	// int i = 0;
	// int j = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			AnserM.m[j][i] = m1.m[j][i] + m2.m[j][i];
		}
	}
	return AnserM;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			AnserM.m[j][i] = m1.m[j][i] - m2.m[j][i];
		}
	}

	return AnserM;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	AnserM.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
	                 m1.m[0][3] * m2.m[3][0];
	AnserM.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
	                 m1.m[0][3] * m2.m[3][1];
	AnserM.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
	                 m1.m[0][3] * m2.m[3][2];
	AnserM.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
	                 m1.m[0][3] * m2.m[3][3];
	AnserM.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
	                 m1.m[1][3] * m2.m[3][0];
	AnserM.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
	                 m1.m[1][3] * m2.m[3][1];
	AnserM.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
	                 m1.m[1][3] * m2.m[3][2];
	AnserM.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
	                 m1.m[1][3] * m2.m[3][3];
	AnserM.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
	                 m1.m[2][3] * m2.m[3][0];
	AnserM.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
	                 m1.m[2][3] * m2.m[3][1];
	AnserM.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
	                 m1.m[2][3] * m2.m[3][2];
	AnserM.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
	                 m1.m[2][3] * m2.m[3][3];
	AnserM.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
	                 m1.m[3][3] * m2.m[3][0];
	AnserM.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
	                 m1.m[3][3] * m2.m[3][1];
	AnserM.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
	                 m1.m[3][3] * m2.m[3][2];
	AnserM.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
	                 m1.m[3][3] * m2.m[3][3];
	return AnserM;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	AnserM.m[0][0] =
	    (+AMatrixMuliply3(m, 223344) + AMatrixMuliply3(m, 233442) + AMatrixMuliply3(m, 243243) -
	     AMatrixMuliply3(m, 243342) - AMatrixMuliply3(m, 233244) - AMatrixMuliply3(m, 223443)) /
	    MatrixAbs(m);

	AnserM.m[0][1] =
	    (-AMatrixMuliply3(m, 123344) - AMatrixMuliply3(m, 133442) - AMatrixMuliply3(m, 143243) +
	     AMatrixMuliply3(m, 143342) + AMatrixMuliply3(m, 133244) + AMatrixMuliply3(m, 123443)) /
	    MatrixAbs(m);

	AnserM.m[0][2] =
	    (+AMatrixMuliply3(m, 122344) + AMatrixMuliply3(m, 132442) + AMatrixMuliply3(m, 142243) -
	     AMatrixMuliply3(m, 142342) - AMatrixMuliply3(m, 132244) - AMatrixMuliply3(m, 122443)) /
	    MatrixAbs(m);

	AnserM.m[0][3] =
	    (-AMatrixMuliply3(m, 122334) - AMatrixMuliply3(m, 132432) - AMatrixMuliply3(m, 142233) +
	     AMatrixMuliply3(m, 142332) + AMatrixMuliply3(m, 132234) + AMatrixMuliply3(m, 122433)) /
	    MatrixAbs(m);

	AnserM.m[1][0] =
	    (-AMatrixMuliply3(m, 213344) - AMatrixMuliply3(m, 233441) - AMatrixMuliply3(m, 243143) +
	     AMatrixMuliply3(m, 243341) + AMatrixMuliply3(m, 233144) + AMatrixMuliply3(m, 213443)) /
	    MatrixAbs(m);

	AnserM.m[1][1] =
	    (+AMatrixMuliply3(m, 113344) + AMatrixMuliply3(m, 133441) + AMatrixMuliply3(m, 143143) -
	     AMatrixMuliply3(m, 143341) - AMatrixMuliply3(m, 133144) - AMatrixMuliply3(m, 113443)) /
	    MatrixAbs(m);

	AnserM.m[1][2] =
	    (-AMatrixMuliply3(m, 112344) - AMatrixMuliply3(m, 132441) - AMatrixMuliply3(m, 142143) +
	     AMatrixMuliply3(m, 142341) + AMatrixMuliply3(m, 132144) + AMatrixMuliply3(m, 112443)) /
	    MatrixAbs(m);

	AnserM.m[1][3] =
	    (+AMatrixMuliply3(m, 112334) + AMatrixMuliply3(m, 132431) + AMatrixMuliply3(m, 142133) -
	     AMatrixMuliply3(m, 142331) - AMatrixMuliply3(m, 132134) - AMatrixMuliply3(m, 112433)) /
	    MatrixAbs(m);

	AnserM.m[2][0] =
	    (+AMatrixMuliply3(m, 213244) + AMatrixMuliply3(m, 223441) + AMatrixMuliply3(m, 243142) -
	     AMatrixMuliply3(m, 243241) - AMatrixMuliply3(m, 223144) - AMatrixMuliply3(m, 213442)) /
	    MatrixAbs(m);

	AnserM.m[2][1] =
	    (-AMatrixMuliply3(m, 113244) - AMatrixMuliply3(m, 123441) - AMatrixMuliply3(m, 143142) +
	     AMatrixMuliply3(m, 143241) + AMatrixMuliply3(m, 123144) + AMatrixMuliply3(m, 113442)) /
	    MatrixAbs(m);

	AnserM.m[2][2] =
	    (+AMatrixMuliply3(m, 112244) + AMatrixMuliply3(m, 122441) + AMatrixMuliply3(m, 142142) -
	     AMatrixMuliply3(m, 142241) - AMatrixMuliply3(m, 122144) - AMatrixMuliply3(m, 112442)) /
	    MatrixAbs(m);

	AnserM.m[2][3] =
	    (-AMatrixMuliply3(m, 112234) - AMatrixMuliply3(m, 122431) - AMatrixMuliply3(m, 142132) +
	     AMatrixMuliply3(m, 142231) + AMatrixMuliply3(m, 122134) + AMatrixMuliply3(m, 112432)) /
	    MatrixAbs(m);

	AnserM.m[3][0] =
	    (-AMatrixMuliply3(m, 213243) - AMatrixMuliply3(m, 223341) - AMatrixMuliply3(m, 233142) +
	     AMatrixMuliply3(m, 233241) + AMatrixMuliply3(m, 223143) + AMatrixMuliply3(m, 213342)) /
	    MatrixAbs(m);

	AnserM.m[3][1] =
	    (+AMatrixMuliply3(m, 113243) + AMatrixMuliply3(m, 123341) + AMatrixMuliply3(m, 133142) -
	     AMatrixMuliply3(m, 133241) - AMatrixMuliply3(m, 123143) - AMatrixMuliply3(m, 113342)) /
	    MatrixAbs(m);

	AnserM.m[3][2] =
	    (-AMatrixMuliply3(m, 112243) - AMatrixMuliply3(m, 122341) - AMatrixMuliply3(m, 132142) +
	     AMatrixMuliply3(m, 132241) + AMatrixMuliply3(m, 122143) + AMatrixMuliply3(m, 112342)) /
	    MatrixAbs(m);

	AnserM.m[3][3] =
	    (+AMatrixMuliply3(m, 112233) + AMatrixMuliply3(m, 122331) + AMatrixMuliply3(m, 132132) -
	     AMatrixMuliply3(m, 132231) - AMatrixMuliply3(m, 122133) - AMatrixMuliply3(m, 112332)) /
	    MatrixAbs(m);

	return AnserM;
}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			AnserM.m[j][i] = m.m[i][j];
		}
	}

	return AnserM;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 AnserM = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	return AnserM;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 AnserM = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	AnserM.m[3][0] = translate.x;
	AnserM.m[3][1] = translate.y;
	AnserM.m[3][2] = translate.z;

	return AnserM;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	AnserM.m[0][0] = scale.x;
	AnserM.m[1][1] = scale.y;
	AnserM.m[2][2] = scale.z;

	return AnserM;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 AnserV = {0.0f, 0.0f, 0.0f};

	AnserV.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	           1.0f * matrix.m[3][0];
	AnserV.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	           1.0f * matrix.m[3][1];
	AnserV.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	           1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
	          1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	AnserV.x /= w;
	AnserV.y /= w;
	AnserV.z /= w;

	return AnserV;
}

float AMatrixMuliply4(Matrix4x4 m, int num) {
	float Anser = 0.0f;

	Anser = m.m[int(num / int(pow(10, 7))) - 1][int(num % int(pow(10, 7)) / int(pow(10, 6))) - 1] *
	        m.m[int(num % int(pow(10, 6)) / int(pow(10, 5))) - 1]
	           [int(num % int(pow(10, 5)) / int(pow(10, 4))) - 1] *
	        m.m[int(num % int(pow(10, 4)) / int(pow(10, 3))) - 1]
	           [int(num % int(pow(10, 3)) / int(pow(10, 2))) - 1] *
	        m.m[int(num % int(pow(10, 2)) / int(pow(10, 1))) - 1]
	           [int(num % int(pow(10, 1)) / int(pow(10, 0))) - 1];

	return Anser;
}

float AMatrixMuliply3(Matrix4x4 m, int num) {
	float Anser = 0.0f;

	Anser = m.m[int(num / int(pow(10, 5))) - 1][int(num % int(pow(10, 5)) / int(pow(10, 4))) - 1] *
	        m.m[int(num % int(pow(10, 4)) / int(pow(10, 3))) - 1]
	           [int(num % int(pow(10, 3)) / int(pow(10, 2))) - 1] *
	        m.m[int(num % int(pow(10, 2)) / int(pow(10, 1))) - 1]
	           [int(num % int(pow(10, 1)) / int(pow(10, 0))) - 1];

	return Anser;
}

float MatrixAbs(Matrix4x4 m) {
	float Anser = 0.0f;

	Anser = AMatrixMuliply4(m, 11223344)

	        + AMatrixMuliply4(m, 11233442)

	        + AMatrixMuliply4(m, 11243243)

	        - AMatrixMuliply4(m, 11243342)

	        - AMatrixMuliply4(m, 11233244)

	        - AMatrixMuliply4(m, 11223443)

	        - AMatrixMuliply4(m, 12213344)

	        - AMatrixMuliply4(m, 13213442)

	        - AMatrixMuliply4(m, 14213243)

	        + AMatrixMuliply4(m, 14213342)

	        + AMatrixMuliply4(m, 13213244)

	        + AMatrixMuliply4(m, 12213443)

	        + AMatrixMuliply4(m, 12233144)

	        + AMatrixMuliply4(m, 13243142)

	        + AMatrixMuliply4(m, 14223143)

	        - AMatrixMuliply4(m, 14233142)

	        - AMatrixMuliply4(m, 13223144)

	        - AMatrixMuliply4(m, 12243143)

	        - AMatrixMuliply4(m, 12233441)

	        - AMatrixMuliply4(m, 13243241)

	        - AMatrixMuliply4(m, 14223341)

	        + AMatrixMuliply4(m, 14233241)

	        + AMatrixMuliply4(m, 13223441)

	        + AMatrixMuliply4(m, 12243341)

	    ;

	return Anser;
}

Matrix4x4 MakeRotateXmatrix(float radian) {
	Matrix4x4 AnserM = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	AnserM.m[1][1] = std::cosf(radian);
	AnserM.m[1][2] = std::sinf(radian);
	AnserM.m[2][1] = -std::sinf(radian);
	AnserM.m[2][2] = std::cosf(radian);

	return AnserM;
}

Matrix4x4 MakeRotateYmatrix(float radian) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	AnserM.m[0][0] = std::cosf(radian);
	AnserM.m[0][2] = -std::sinf(radian);
	AnserM.m[2][0] = std::sinf(radian);
	AnserM.m[2][2] = std::cosf(radian);

	return AnserM;
}

Matrix4x4 MakeRotateZmatrix(float radian) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	AnserM.m[0][0] = std::cosf(radian);
	AnserM.m[0][1] = std::sinf(radian);
	AnserM.m[1][0] = -std::sinf(radian);
	AnserM.m[1][1] = std::cosf(radian);

	return AnserM;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	Matrix4x4 ScaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 RotateMatrixX = MakeRotateXmatrix(rot.x);
	Matrix4x4 RotateMatrixY = MakeRotateYmatrix(rot.y);
	Matrix4x4 RotateMatrixZ = MakeRotateZmatrix(rot.z);
	Matrix4x4 RotateMatrixXYZ = Multiply(RotateMatrixX, Multiply(RotateMatrixY, RotateMatrixZ));

	Matrix4x4 TranslationMatrix = MakeTranslateMatrix(translate);

	for (int i = 0; i < 3; i++) {
		AnserM.m[0][i] = ScaleMatrix.m[0][0] * RotateMatrixXYZ.m[0][i];
	}

	for (int i = 0; i < 3; i++) {
		AnserM.m[1][i] = ScaleMatrix.m[1][1] * RotateMatrixXYZ.m[1][i];
	}

	for (int i = 0; i < 3; i++) {
		AnserM.m[2][i] = ScaleMatrix.m[2][2] * RotateMatrixXYZ.m[2][i];
	}

	for (int i = 0; i < 3; i++) {
		AnserM.m[3][i] = TranslationMatrix.m[3][i];
	}

	return AnserM;
}

Vector3 TransforNormal(const Vector3& v, const Matrix4x4& m) { 
	
	Vector3 AnserV = {0.0f, 0.0f, 0.0f}; 

	AnserV = {
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};


	return AnserV;
}

Matrix4x4 MakePerspectiveFovMatrix(float FovY, float AspectRatio, float NearClip, float FarClip) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	FovY;
	AspectRatio;
	NearClip;
	FarClip;

	AnserM.m[0][0] = 1.0f / tanf(FovY / 2.0f) / AspectRatio;

	AnserM.m[1][1] = 1.0f / tanf(FovY / 2.0f);

	AnserM.m[2][2] = FarClip / (FarClip - NearClip);

	AnserM.m[3][2] = -NearClip * FarClip / (FarClip - NearClip);

	return AnserM;
}

Matrix4x4 MakeOrthoGraphicMatrix(
    float Left, float Top, float Right, float Bottom, float NearClip, float FarClip) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	Left;
	Top;
	Right;
	Bottom;
	NearClip;
	FarClip;

	AnserM.m[0][0] = 2 / (Right - Left);

	AnserM.m[1][1] = 2 / (Top - Bottom);

	AnserM.m[2][2] = 1 / (FarClip - NearClip);

	AnserM.m[3][0] = (Left + Right) / (Left - Right);

	AnserM.m[3][1] = (Top + Bottom) / (Bottom - Top);

	AnserM.m[3][2] = NearClip / (NearClip - FarClip);

	return AnserM;
}

Matrix4x4 MakeViewportMatrix(
    float Left, float Top, float Width, float Height, float MinDepth, float MaxDepth) {
	Matrix4x4 AnserM = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	Left;
	Top;
	Width;
	Height;
	MinDepth;
	MaxDepth;

	AnserM.m[0][0] = Width / 2;

	AnserM.m[1][1] = -(Height / 2);

	AnserM.m[2][2] = MaxDepth - MinDepth;

	AnserM.m[3][0] = Left + (Width / 2);

	AnserM.m[3][1] = Top + (Height / 2);

	AnserM.m[3][2] = MinDepth;

	return AnserM;
}
