#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
class Player {
	
public:

	void Initialize(Model *model,uint32_t TextureHundle);

	void Update();

	void Draw(ViewProjection ViewProjection);


private:

	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

	
	Input* Input_ = nullptr;

	const float MOVELIMITX = 36;
	const float MOVELIMITY = 20;
};
