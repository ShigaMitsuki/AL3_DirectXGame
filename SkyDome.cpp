#include "SkyDome.h"

#include <cassert>
void SkyDome::Initialize(Model* model) {

	assert(model);
	Model_ = model;

	WorldTransform_.Initialize();

	WorldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	float scale = 2.0f;
	WorldTransform_.scale_ = {scale, scale, scale};
}

void SkyDome::Update() {

	
	WorldTransform_.rotation_.y += 0.0001f;
	WorldTransform_.UpdateMatrix();

}


void SkyDome::Draw(ViewProjection ViewProjection_) {
	Model_->Draw(WorldTransform_, ViewProjection_);

}
