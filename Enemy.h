#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Vector3.h"
class Enemy {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(ViewProjection ViewProjection);

private:

	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	Vector3 Velocity_;

	enum class Phase {
		Approach,
		Leave,
	};

	Phase Phase_ = Phase::Approach;

	void Approach();

	void Leave();

	static void(Enemy::*spFuncTable[])();
};
