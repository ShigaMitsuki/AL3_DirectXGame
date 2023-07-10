#pragma once

#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"


class RailCamera {

	public:

void Initialize(Vector3 worldtransform, Vector3 rad);

const ViewProjection& GetViewProjection() { return ViewProjecion_; }

void Update();

const WorldTransform& GetWorldTransform() { return WorldTransform_; };

private:

	WorldTransform WorldTransform_;

	ViewProjection ViewProjecion_;

	Vector3 Rad_;
	float Speed_;
};
