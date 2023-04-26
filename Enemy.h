#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Vector3.h"

class Enemy;


class BaseEnemyPhase {
public:
	virtual void Update(Enemy* enemy);
};

class EnemyPhaseApproach : public BaseEnemyPhase {
public:
	void Update(Enemy* enemy);
};

class EnemyPhaseLeave : public BaseEnemyPhase {
public:
	void Update(Enemy* enemy);
};

class Enemy {
public:

	Enemy();
	~Enemy();

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(ViewProjection ViewProjection);

	void Move(Vector3 MoveVelocity);

	void ChangePhase(BaseEnemyPhase* NextPhase);

	Vector3 ReturnTranslation() { return WorldTransform_.translation_; };

private:

	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	Vector3 Velocity_;

	/*enum class Phase {
		Approach,
		Leave,
	};

	Phase Phase_ = Phase::Approach;*/

	void Approach();

	void Leave();

	static void(Enemy::*spFuncTable[])();

	BaseEnemyPhase* Phase;
};

