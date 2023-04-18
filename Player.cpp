#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t TextureHundle) { 
	assert(model);
	
	Model_ = model;
	TextureHundle_ = TextureHundle;

	WorldTransform_.Initialize();

}

void Player::Update() { 
	WorldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection ViewProjection) {

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
}
