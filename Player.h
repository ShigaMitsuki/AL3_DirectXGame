#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"
#include "Input.h"
#include "Collider.h"
#include <list>
class Player : public Collider {
	
public:

	~Player();

	void Initialize(Model *model,uint32_t TextureHundle);

	void Update();

	void Rotate();

	void Attack();

	void Draw(ViewProjection ViewProjection);

	virtual Vector3 GetWorldPosition();

	//void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() { return Bullets_; };

	virtual void OnCollision();

private:

	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	std::list<PlayerBullet*> Bullets_;

	
	Input* Input_ = nullptr;

	const float MOVELIMITX = 36;
	const float MOVELIMITY = 20;
};
