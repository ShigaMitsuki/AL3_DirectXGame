#include "PlayerBullet.h"
#include "CollisionConfig.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model); 

	Model_ = model;	

	TextureHundle_ = TextureManager::Load("CyclamenPink.jpg");

	WorldTransform_.Initialize();

	WorldTransform_.translation_ = position;

	Velocity_ = velocity;

	SetCollisionAttribute(kCollisionAttributePlayer);

	SetCollisionMask(kCollisionAttributePlayer);
}

void PlayerBullet::Update() {

	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Velocity_);

	WorldTransform_.UpdateMatrix();

	if (--DeathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Rotate() {}

void PlayerBullet::Draw(ViewProjection ViewProjection) {

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
}

void PlayerBullet::OnCollision() {
	
	isDead_ = true;

}

Vector3 PlayerBullet::GetWorldPosition() {

	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}
