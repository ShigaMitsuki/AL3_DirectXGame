#pragma once
#include "Model.h"
#include "WorldTransform.h"
class Player {
public:

	void Initialize(Model *model,uint32_t TextureHundle);

	void Update();

	void Draw(ViewProjection ViewProjection);


private:

	WorldTransform WorldTransform_;

	Model* Model_ = nullptr;

	uint32_t TextureHundle_ = 0u;

};
