#include "SkyDome.h"

#include <cassert>
void SkyDome::Initialize(Model* model) {

	assert(model);
	Model_ = model;

	WorldTransform_.Initialize();

	WorldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void SkyDome::Update() {

	

	WorldTransform_.UpdateMatrix();

}


void SkyDome::Draw(ViewProjection ViewProjection_) {
	Model_->Draw(WorldTransform_, ViewProjection_);

}
