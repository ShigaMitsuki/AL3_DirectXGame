#include "Player.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t TextureHundle) { 
	assert(model);
	
	Model_ = model;
	TextureHundle_ = TextureHundle;

	WorldTransform_.Initialize();

	Input_ = Input::GetInstance();

}

void Player::Update() {
	WorldTransform_.TransferMatrix();

	Vector3 Move = {0.0f, 0.0f, 0.0f};

	const float CHARACTORSPEED = 0.2f;
	CHARACTORSPEED;

	if (Input_->PushKey(DIK_LEFT)) {
		Move.x -= CHARACTORSPEED;
	} else if (Input_->PushKey(DIK_RIGHT)) {
		Move.x += CHARACTORSPEED;
	}

	if (Input_->PushKey(DIK_UP)) {
		Move.y -= CHARACTORSPEED;
	} else if (Input_->PushKey(DIK_DOWN)) {
		Move.y += CHARACTORSPEED;
	}

	/*Matrix4x4 ScaleMatrix = MakeScaleMatrix(WorldTransform_.scale_);

	Matrix4x4 RotateMatrixX = MakeRotateXmatrix(WorldTransform_.rotation_.x);
	Matrix4x4 RotateMatrixY = MakeRotateYmatrix(WorldTransform_.rotation_.y);
	Matrix4x4 RotateMatrixZ = MakeRotateZmatrix(WorldTransform_.rotation_.z);
	Matrix4x4 RotateMatrixXYZ = Multiply(RotateMatrixX, Multiply(RotateMatrixY, RotateMatrixZ)); 
	
	Matrix4x4 TranslationMatrix = MakeTranslateMatrix(WorldTransform_.translation_);*/

	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Move);

	WorldTransform_.matWorld_ = MakeAffineMatrix(
	    WorldTransform_.scale_, WorldTransform_.translation_, WorldTransform_.translation_);

}

void Player::Draw(ViewProjection ViewProjection) {

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
}
