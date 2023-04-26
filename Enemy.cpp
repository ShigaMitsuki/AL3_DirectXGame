#include "Enemy.h"

#include <iostream>
Enemy::Enemy() {
	Phase = new EnemyPhaseApproach();

	Velocity_ = {0.0f, 0.0f, 0.0f};
}

Enemy::~Enemy() { 
	delete Phase;
}

void Enemy::Initialize(Model* model, const Vector3& position) {
	WorldTransform_.Initialize();
	Model_ = model;

	WorldTransform_.translation_ = position;

	TextureHundle_ = TextureManager::Load("Green.jpg");

	Velocity_ = {0.0f , 0.0f , -0.5f};
}

void (Enemy::*Enemy::spFuncTable[])() = {
	&Enemy::Approach,
    &Enemy::Leave
};



void Enemy::Update() {

	/*switch(Phase_) { 
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave(); 
		break;
	}	*/
	
	//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07
	// 02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07
	// 02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07
	// 02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07

	//(this->*spFuncTable[static_cast<size_t>(Phase_)])();
	Phase->Update(this);

	WorldTransform_.UpdateMatrix();

}

void Enemy::Approach() {
	Velocity_;
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, {0.0f, 0.0f, -0.5f});

	if (WorldTransform_.translation_.z < 0.0f) {
		//Phase_ = Phase::Leave;
	}

}

void Enemy::Leave() {
	Velocity_ ;
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, {0.0f, 1.0f, 0.0f});
}

void Enemy::Draw(ViewProjection viewProjection) {

	Model_->Draw(WorldTransform_, viewProjection, TextureHundle_);
	
}

void Enemy::Move(Vector3 MoveVelocity) {
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, MoveVelocity);
}

void Enemy::ChangePhase(BaseEnemyPhase* NextPhase) { 
	delete Phase;
	Phase = NextPhase;
}

void BaseEnemyPhase::Update(Enemy* enemy) { enemy; }

void EnemyPhaseApproach::Update(Enemy* enemy) {

	enemy->Move({0.0f, 0.0f, -0.5f});

	if (enemy->ReturnTranslation().z < 0.0f) {
		enemy->ChangePhase(new EnemyPhaseLeave);
	}

}
void EnemyPhaseLeave::Update(Enemy* enemy) {

	
	enemy->Move({0.0f, 0.5f, 0.0f});

}
