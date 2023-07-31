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

	void Initialize(Model* model, uint32_t TextureHundle, Vector3 Pos,Model* mahoujin_model);

	void Init(Vector3 Pos);

	void Update(ViewProjection viewProjection);

	void Rotate();

	void Attack();

	void Draw(ViewProjection ViewProjection);

	void DrawUI();

	virtual Vector3 GetWorldPosition();

	Vector3 GetPos() { return WorldTransform_.translation_ ; };

	bool GetDeadFlag() { return deadFlag; };
	

	//void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() { return Bullets_; };

	virtual void OnCollision();

	void SetParent(const WorldTransform* parent);

	void SetCharge(bool charge) { Charging = charge; };

	float GetMahouJinScale() { return MahouJinWorldTransform_.scale_.x; };

	Vector3 GetMahouJinPos();

	void MahouJin(XINPUT_STATE joyState_);

	bool kusoga() { return OshitazoGomi; };

private:

	WorldTransform WorldTransform_;

	WorldTransform ReticleWorldTransform_;

	WorldTransform MahouJinWorldTransform_;

	Model* Model_ = nullptr;
	Sprite* reticleSprite = nullptr;

	Sprite* HPSprite0 = nullptr;
	Sprite* HPSprite1 = nullptr;
	Sprite* HPSprite2 = nullptr;

	Model* MahouJinMdel_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	std::list<PlayerBullet*> Bullets_;
	
	Input* Input_ = nullptr;

	bool Charging = false;

	bool OshitazoGomi = false;

	bool Mahoujing = false;

	bool MahoujinOn = false;

	int HP = 1;

	int invTime;

	bool deadFlag = false;

	int shine = 0;

	const float MOVELIMITX = 14;
	const float MOVELIMITY = 8;
};
