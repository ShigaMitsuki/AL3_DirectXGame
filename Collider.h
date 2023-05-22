#pragma once
#include "Vector3.h"

class Collider {

	private:

		float Radius_ = 1.0f;

		
	
	public:

		void SetRadius(float radius) { Radius_ = radius; };

		float GetRadius() { return Radius_; };

		virtual void OnCollision() { ; };

		virtual Vector3 GetWorldPosition() = 0;
};
