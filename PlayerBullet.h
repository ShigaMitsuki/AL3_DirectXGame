#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "Input.h"
class PlayerBullet {

	public:

	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	void Update();

	void Rotate();

	void Draw(ViewProjection ViewProjection);

	bool isDead() const { return isDead_; };

	private:
	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	Input* Input_ = nullptr;

	Vector3 Velocity_;

	static const int32_t LIFETIME = 60 * 5;

	int32_t DeathTimer_ = LIFETIME;

	bool isDead_ = false;
};
