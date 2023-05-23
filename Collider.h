#pragma once
#include "Vector3.h"
#include <cstdint>

class Collider {
	

private:
	float Radius_ = 1.0f;

	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t CollisionMask_ = 0xffffffff;

public:
	void SetRadius(float radius) { Radius_ = radius; };

	float GetRadius() { return Radius_; };

	virtual void OnCollision() { ; };

	virtual Vector3 GetWorldPosition() = 0;

	uint32_t GetCollisionAttribute() { return collisionAttribute_; };

	void SetCollisionAttribute(uint32_t ca) { collisionAttribute_ = ca; };

	uint32_t GetCollisionMask() { return CollisionMask_; };

	void SetCollisionMask(uint32_t cm) { CollisionMask_ = cm; };
};
