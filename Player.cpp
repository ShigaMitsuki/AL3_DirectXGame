#include "Player.h"
#include "Matrix4x4.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t TextureHundle) { 
	assert(model);
	
	Model_ = model;
	TextureHundle_ = TextureHundle;

	WorldTransform_.Initialize();

	/*Input_ = Input::GetInstance();*/

}

void Player::Update() {
	WorldTransform_.TransferMatrix();

	/*Vector3 Move = {0.0f, 0.0f, 0.0f};

	const float CHARACTORSPEED = 0.2f;

	if (Input_->PushKey(DIK_LEFT)) {
		Move.x -= CHARACTORSPEED;
	} else if (Input_->PushKey(DIK_RIGHT)) {
		Move.x += CHARACTORSPEED;
	}

	if (Input_->PushKey(DIK_UP)) {
		Move.y -= CHARACTORSPEED;
	} else if (Input_->PushKey(DIK_DOWN)) {
		Move.y += CHARACTORSPEED;
	}*/

	/*Matrix4x4 ScaleMatrix = {
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f};



	ScaleMatrix.m[0][0] = WorldTransform_.scale_.x;
	ScaleMatrix.m[1][1] = WorldTransform_.scale_.x;
	ScaleMatrix.m[2][2] = WorldTransform_.scale_.x;

	Matrix4x4 RotateMatrixX;
	Matrix4x4 RotateMatrixY;
	Matrix4x4 RotateMatrixY;*/

	
}

void Player::Draw(ViewProjection ViewProjection) {

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
}
