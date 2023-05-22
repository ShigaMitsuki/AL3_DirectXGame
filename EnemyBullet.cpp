#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	Model_ = model;

	TextureHundle_ = TextureManager::Load("Lime.png");

	WorldTransform_.scale_.x = 0.5f;
	WorldTransform_.scale_.y = 0.5f;
	WorldTransform_.scale_.z = 3.0f;

	WorldTransform_.Initialize();

	Velocity_ = velocity;

	WorldTransform_.rotation_.y = std::atan2f(Velocity_.x, Velocity_.z);
	float XZ = sqrtf(Velocity_.x * Velocity_.x + Velocity_.z * Velocity_.z);

	WorldTransform_.rotation_.x = std::atan2f(-Velocity_.y, XZ);

	WorldTransform_.translation_ = position;
	WorldTransform_.UpdateMatrix();

	
}

Vector3 EnemyBullet::GetWorldPosition() {

	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}

void EnemyBullet::OnCollision() { 
	isDead_ = true; }

void EnemyBullet::Update() {

	Vector3 PlayerPos = Player_->GetWorldPosition();
	Vector3 ThisPos = GetWorldPosition();

	Vector3 ToPlayer = Subtract(PlayerPos, ThisPos);

	ToPlayer = Normalize(ToPlayer);
	Velocity_ = Normalize(Velocity_);

	Velocity_ = Multiply(1.0f , Slerp(Velocity_, ToPlayer, 0.05f));
	
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Velocity_);

	WorldTransform_.rotation_.y = std::atan2f(Velocity_.x, Velocity_.z);
	float XZ = sqrtf(Velocity_.x * Velocity_.x + Velocity_.z * Velocity_.z);

	WorldTransform_.rotation_.x = std::atan2f(-Velocity_.y, XZ);

	WorldTransform_.UpdateMatrix();

	if (--DeathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Rotate() {}

void EnemyBullet::Draw(ViewProjection ViewProjection) {

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
}
