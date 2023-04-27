#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	Model_ = model;

	TextureHundle_ = TextureManager::Load("Lime.png");

	WorldTransform_.Initialize();

	WorldTransform_.translation_ = position;

	Velocity_ = velocity;
}

void EnemyBullet::Update() {

	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Velocity_);

	WorldTransform_.UpdateMatrix();

	if (--DeathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Rotate() {}

void EnemyBullet::Draw(ViewProjection ViewProjection) {

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
}
