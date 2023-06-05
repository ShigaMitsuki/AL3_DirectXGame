#pragma once
#include <list>
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
class CollisionManager {

	private:
	

	std::list<Collider*> colliders_;

	public:

		
	CollisionManager();

	//~CollisionManager();
	void Clear();

	void Colpush(Player* player, Enemy* enemy);

	void CheckAllCollisions();

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
