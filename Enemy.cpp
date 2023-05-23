#include "Enemy.h"
#include "Player.h"
#include <cassert>
#include <iostream>
#include "CollisionConfig.h"
Enemy::Enemy() {
	Phase = new EnemyPhaseApproach();

	Velocity_ = {0.0f, 0.0f, 0.0f};

	//ShotFunc = std::bind(&Enemy::Shot, this ,std::placeholders::_1, std::placeholders::_2);
}

Enemy::~Enemy() { 
	delete Phase;

	for (EnemyBullet* bullet : Bullets_) {

		delete bullet;
	}

	for (TimeCall* timecall : TimeCall_) {

		delete timecall;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position) {
	WorldTransform_.Initialize();
	Model_ = model;

	WorldTransform_.translation_ = position;

	TextureHundle_ = TextureManager::Load("Green.jpg");

	Velocity_ = {0.0f , 0.0f , -0.5f};

	TimeShot();

	SetCollisionAttribute(kCollisionAttributeEnemy);

	SetCollisionMask(kCollisionAttributePlayer);
}

void (Enemy::*Enemy::spFuncTable[])() = {
	&Enemy::Approach,
    &Enemy::Leave
};



void Enemy::Update() {

	Bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {

			delete bullet;
			return true;
		}
		return false;
	});

	/*switch(Phase_) {
	case Phase::Approach:
	default:
	    Approach();
	    break;
	case Phase::Leave:
	    Leave();
	    break;
	}	*/

	// 02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07
	//  02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07
	//  02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07
	//  02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07//02_07

	//(this->*spFuncTable[static_cast<size_t>(Phase_)])();
	Phase->Update(this);

	for (EnemyBullet* bullet : Bullets_) {

		bullet->Update();
	}

	TimeCall_.remove_if([](TimeCall* timecall ) {
		if (timecall->IsFinished()) {

			delete timecall;

			return true;
		}
		return false;
	});

	for (TimeCall* timecall : TimeCall_) {
		timecall->Update();
	}

	WorldTransform_.UpdateMatrix();
};

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

	for (EnemyBullet* bullet : Bullets_) {

		bullet->Draw(viewProjection);
	}
	
}

void Enemy::Move(Vector3 MoveVelocity) {
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, MoveVelocity);
}

void Enemy::ChangePhase(BaseEnemyPhase* NextPhase) { 
	delete Phase;
	Phase = NextPhase;
}

void Enemy::Shot(Vector3 Pos, Vector3 Vel) {

	assert(Player_);
	Vel;
	const float BULEETSPEED = 1.0f;

	Vector3 PlayerPos = Player_->GetWorldPosition();
	Vector3 ThisPos = GetWorldPosition();
	
	Vector3 PosDistance = Subtract(PlayerPos, ThisPos);
	Vector3 PosDistanceN = Normalize(PosDistance);

	Vector3 velocity = Multiply(BULEETSPEED, PosDistanceN);
	velocity = TransforNormal(velocity, WorldTransform_.matWorld_);

	//Vector3 velocity(Vel);
	//velocity = TransforNormal(velocity, WorldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	

	newBullet->Initialize(Model_, Pos, velocity);
	newBullet->SetPlayer(Player_);

	Bullets_.push_back(newBullet);
}

void Enemy::TimeShot() {
	
	Shot(WorldTransform_.translation_, {0.0f, 0.0f, -1.0f});

	TimeCall_.push_back(new TimeCall(std::bind(&Enemy::TimeShot,this),60));

}

Vector3 Enemy::GetWorldPosition() {

	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}

void Enemy::OnCollision() {}

void BaseEnemyPhase::Update(Enemy* enemy) { enemy; }

void EnemyPhaseApproach::Update(Enemy* enemy) {

	enemy->Move({0.0f, 0.0f, -0.5f});

	//if (ShotCoolDown_ < 0) {
	//	//enemy->Shot(enemy->ReturnTranslation(), {0.0f, 0.0f, -1.0f});
	//	
	//	ShotCoolDown_ = SHOTCOOLDOWN;
	//} else {
	//	ShotCoolDown_--;
	//}

	//enemy->TimeShot();

	if (enemy->ReturnTranslation().z < 0.0f) {
		enemy->ChangePhase(new EnemyPhaseLeave);
	}

}
void EnemyPhaseLeave::Update(Enemy* enemy) {

	
	enemy->Move({0.0f, 0.5f, 0.0f});

}
