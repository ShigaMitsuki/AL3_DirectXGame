#include "PlayerBullet.h"
#include "Player.h"
#include "CollisionConfig.h"
#include <imgui.h>
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model); 

	Model_ = model;	

	TextureHundle_ = TextureManager::Load("CyclamenPink.jpg");

	WorldTransform_.Initialize();

	WorldTransform_.translation_ = position;


	WorldTransform_.scale_ = {0.1f, 0.1f, 1.0f};

	Input_ = Input::GetInstance();

	Velocity_ = velocity;

	SetCollisionAttribute(kCollisionAttributePlayer);

	SetCollisionMask(~kCollisionAttributePlayer);
}

void PlayerBullet::Update() {

	assert(Player_);

	if (WorldTransform_.scale_.x <= MahouJinScale && shotFlag == false) {

		/*(Length(Subtract(GetWorldPosition(), Player_->GetWorldPosition())) > 100.0f) {
			isDead_ = true;
			return;
		}*/
		
		if (Player_->kusoga() == true) {
			// Attack();

			isDead_ = true;
			Player_->SetCharge(false);

			return;
		}
		

		Vector3 scalePlus = {0.05f, 0.05f, 0.0f};

		

		WorldTransform_.scale_ = Add(WorldTransform_.scale_, scalePlus);

		Vector3 scalePlusPos = {0.0f, 0.0f, 0.0f};

		WorldTransform_.translation_ =  Add(WorldTransform_.translation_, Multiply(1.0f, scalePlusPos));

		if (WorldTransform_.scale_.x >= MahouJinScale) {
			DeathTimer_ = LIFETIME;
			shotFlag = true;
			Player_->SetCharge(false);
		} 
	}

	/*ImGui::Begin("Mahoujin");

	ImGui::Text(
	    "Bullet:(%+.2f,%+.2f,%+.2f)", GetWorldPosition().x, GetWorldPosition().y,
	    GetWorldPosition().z);

	ImGui::Text(
	    "MAhoujin:(%+.2f,%+.2f,%+.2f)", Player_->GetMahouJinPos().x, Player_->GetMahouJinPos().y,
	    Player_->GetMahouJinPos().z);

	ImGui::End();*/

	if (shotFlag == true) {

			WorldTransform_.translation_ = Add(WorldTransform_.translation_, Velocity_);

	}

	/*if (Input_->PushKey(DIK_SPACE)) {
		Vector3 scalePlus = {0.1f, 0.1f, 0.1f};

		WorldTransform_.scale_ = Add(WorldTransform_.scale_, scalePlus);
		
	}
	 
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Velocity_);*/
	//WorldTransform_.translation_ = Add(WorldTransform_.translation_, Velocity_);
	WorldTransform_.UpdateMatrix();

	if (--DeathTimer_ <= 0) {
		isDead_ = true;
	}
	


}

void PlayerBullet::Rotate() {}

void PlayerBullet::Draw(ViewProjection ViewProjection) {

	//Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
	Model_->Draw(WorldTransform_, ViewProjection);
}

void PlayerBullet::OnCollision() {
	
	//isDead_ = true;

}

Vector3 PlayerBullet::GetWorldPosition() {

	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}
