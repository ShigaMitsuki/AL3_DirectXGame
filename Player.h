#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"
#include "Input.h"
#include "Collider.h"
#include <list>
#include <Sprite.h>
class Player : public Collider {
	
public:

	~Player();

	void Initialize(Model* model, uint32_t TextureHundle, Vector3 Pos);

	void Update(ViewProjection viewProjection);

	void Rotate();

	void Attack();

	void Draw(ViewProjection ViewProjection);

	void DrawUI();

	virtual Vector3 GetWorldPosition();

	//void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() { return Bullets_; };

	virtual void OnCollision();

	void SetParent(const WorldTransform* parent);

private:

	WorldTransform WorldTransform_;

	WorldTransform ReticleWorldTransform_;

	Model* Model_ = nullptr;
	Sprite* reticleSprite = nullptr;

	uint32_t TextureHundle_ = 0u;

	std::list<PlayerBullet*> Bullets_;

	
	Input* Input_ = nullptr;

	const float MOVELIMITX = 36;
	const float MOVELIMITY = 20;
};
