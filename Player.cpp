#pragma once
#include "Player.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "ImGuiManager.h"
#include <cassert>
#include "CollisionConfig.h"

Player::~Player() {

	for (PlayerBullet* bullet : Bullets_) {

		delete bullet;
	}
}

void Player::Initialize(Model* model, uint32_t TextureHundle) { 
	assert(model);
	
	Model_ = model;
	TextureHundle_ = TextureHundle;

	WorldTransform_.Initialize();

	Input_ = Input::GetInstance();


	SetCollisionAttribute(kCollisionAttributePlayer);

	SetCollisionMask(kCollisionAttributePlayer);
}

void Player::Update() {

	Bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {

			delete bullet;
			return true;
		}
		return false;
	});

	WorldTransform_.TransferMatrix();

	Vector3 Move = {0.0f, 0.0f, 0.0f};

	

	const float CHARACTORSPEED = 0.2f;
	

	if (Input_->PushKey(DIK_LEFT)) {
		Move.x -= CHARACTORSPEED;
	} else if (Input_->PushKey(DIK_RIGHT)) {
		Move.x += CHARACTORSPEED;
	}

	if (Input_->PushKey(DIK_UP)) {
		Move.y += CHARACTORSPEED;
	} else if (Input_->PushKey(DIK_DOWN)) {
		Move.y -= CHARACTORSPEED;
	}

	/*Matrix4x4 ScaleMatrix = MakeScaleMatrix(WorldTransform_.scale_);

	Matrix4x4 RotateMatrixX = MakeRotateXmatrix(WorldTransform_.rotation_.x);
	Matrix4x4 RotateMatrixY = MakeRotateYmatrix(WorldTransform_.rotation_.y);
	Matrix4x4 RotateMatrixZ = MakeRotateZmatrix(WorldTransform_.rotation_.z);
	Matrix4x4 RotateMatrixXYZ = Multiply(RotateMatrixX, Multiply(RotateMatrixY, RotateMatrixZ)); 
	
	Matrix4x4 TranslationMatrix = MakeTransl0-ateMatrix(WorldTransform_.translation_);*/

	Rotate();

	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Move);

	/*WorldTransform_.matWorld_ = MakeAffineMatrix(
	    WorldTransform_.scale_, WorldTransform_.rotation_, WorldTransform_.translation_);*/
	
	WorldTransform_.UpdateMatrix();

	WorldTransform_.translation_.x =
	    std::clamp(WorldTransform_.translation_.x, -MOVELIMITX, MOVELIMITX);

	WorldTransform_.translation_.y =std::clamp(WorldTransform_.translation_.y, -MOVELIMITY,MOVELIMITY);

	ImGui::Begin("Player");
	float DebugPos[3] = {
	    WorldTransform_.translation_.x, WorldTransform_.translation_.y,WorldTransform_.translation_.z};
	ImGui::SliderFloat3("Pos", DebugPos, -MOVELIMITX, MOVELIMITX);
	ImGui::End();

	WorldTransform_.translation_ = {DebugPos[0], DebugPos[1], DebugPos[2]};

	Attack();

	for (PlayerBullet* bullet : Bullets_) {
	
	bullet->Update();
	}
	
	//Bullet_ != nullptr;
	

}

void Player::Rotate() {

	const float ROTSPEED = 0.05f;

	if (Input_->PushKey(DIK_A)) {
		WorldTransform_.rotation_.y -= ROTSPEED;
	} else if (Input_->PushKey(DIK_D)) {
		WorldTransform_.rotation_.y += ROTSPEED;
	}
}

void Player::Attack() {

	if (Input_->TriggerKey(DIK_SPACE)) {

		const float BULEETSPEED = 1.0f;
		Vector3 velocity(0, 0, BULEETSPEED);

		velocity = TransforNormal(velocity , WorldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(Model_, WorldTransform_.translation_, velocity);

		Bullets_.push_back(newBullet);
	}
}

void Player::Draw(ViewProjection ViewProjection) {

	for (PlayerBullet* bullet : Bullets_){
	
	bullet->Draw(ViewProjection);
	}

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);

	
}

Vector3 Player::GetWorldPosition() { 
	
	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos; 



}

void Player::OnCollision() {}
