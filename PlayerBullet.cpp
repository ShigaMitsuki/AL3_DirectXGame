#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model); 

	Model_ = model;

	TextureHundle_ = TextureManager::Load("CyclamenPink.jpg");

	WorldTransform_.Initialize();

	WorldTransform_.translation_ = position;

	Velocity_ = velocity;
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
