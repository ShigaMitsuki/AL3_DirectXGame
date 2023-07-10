#pragma once
#include "Model.h"
#include "WorldTransform.h"

class SkyDome {

	public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection ViewProjection_);

	private:

		WorldTransform WorldTransform_;

		Model* Model_ = nullptr;

};
