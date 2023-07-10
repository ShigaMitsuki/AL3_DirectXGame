#include "CollisionManager.h"
#include "GameScene.h"
#include <cassert>
CollisionManager::CollisionManager() {}

void CollisionManager::Clear() {

	colliders_.clear();

}


void CollisionManager::CheckAllCollisions(Player* player, Enemy* enemy, GameScene* gameSccne) {

	
	
	const std::list<PlayerBullet*>& PlayerBullets = player->GetBullets();
	const std::list<EnemyBullet*>& EnemyBullets = gameSccne->GetBullets();

	colliders_.push_back(player);
	colliders_.push_back(enemy);
	// enemy;
	for (EnemyBullet* bullet : EnemyBullets) {
		colliders_.push_back(bullet);
	}
	for (PlayerBullet* bullet : PlayerBullets) {
 		colliders_.push_back(bullet);
	}
	
	std::list<Collider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {
		// Collider colliderA = colliders_.

		Collider* A = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* B = *itrB;

			if (

			    ((A->GetCollisionAttribute() & B->GetCollisionMask()) == 0) ||
			    ((B->GetCollisionAttribute() & A->GetCollisionMask()) == 0)

			) {
				continue;
			}
			CheckCollisionPair(A, B);
		}
	}
}

//CollisionManager::~CollisionManager() { delete CM; }

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	Vector3 posA = colliderA->GetWorldPosition();
	Vector3 posB = colliderB->GetWorldPosition();

	if (Distance(posA, posB) < 8.0f) {
		colliderA->OnCollision();

		colliderB->OnCollision();
	}
}
