#pragma once
#include "Input.h"
#include "Model.h"
#include "Vector3.h"
#include "Player.h"
#include "WorldTransform.h"
#include "Collider.h"
class EnemyBullet : public Collider {

public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Rotate();

	void Draw(ViewProjection ViewProjection);

	virtual Vector3 GetWorldPosition();

	bool isDead() const { return isDead_; };

	void SetPlayer(Player* player) { Player_ = player; };

	virtual void OnCollision();

private:
	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	Vector3 Velocity_;

	static const int32_t LIFETIME = 60 * 5;

	int32_t DeathTimer_ = LIFETIME;

	Player* Player_ = nullptr;

	bool isDead_ = false;
};
