#include "RailCamera.h"
#include "ImGui.h"

void RailCamera::Initialize(Vector3 worldtransform, Vector3 rad) {

		//WorldTransform_.Initialize();
		WorldTransform_.translation_ = worldtransform;
	    WorldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

		ViewProjecion_.Initialize();
	    Rad_ = rad;

		Speed_ = -0.1f;
}

void RailCamera::Update() {
	
	ImGui::Begin("RailCamera");
	ImGui::DragFloat3("Pos", &WorldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("Rot", &WorldTransform_.rotation_.x, 0.01f);
	ImGui::End();

	


	Vector3 Velocity = {0.0f, 0.0f, Speed_};
	Vector3 RotPlus = {0.0f, 0.0f, 0.0f};

	WorldTransform_.translation_ = Add(Velocity, WorldTransform_.translation_);
	WorldTransform_.rotation_ = Add(RotPlus, WorldTransform_.rotation_);

	WorldTransform_.matWorld_ = Inverse(MakeAffineMatrix(
	    WorldTransform_.scale_, WorldTransform_.rotation_, WorldTransform_.translation_));
	
	ViewProjecion_.matView = Inverse(WorldTransform_.matWorld_);

	ViewProjecion_.TransferMatrix();
}
