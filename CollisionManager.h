#pragma once
#include <list>
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"

//class CollisionManager;
//class GameScene;

class CollisionManager {
	private:
	

	std::list<Collider*> colliders_;

	public:

		
	CollisionManager();

	//~CollisionManager();
	void Clear();

	void CheckAllCollisions(Player* player, Enemy* enemy, GameScene* gameSccne);

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
