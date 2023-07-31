#pragma once
#include "Player.h"
#include "CollisionConfig.h"
#include "ImGuiManager.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cassert>

Player::~Player() {

	for (PlayerBullet* bullet : Bullets_) {

		delete bullet;
	}

	delete reticleSprite;

	delete HPSprite0;
	delete HPSprite1;
	delete HPSprite2;
}

void Player::Initialize(Model* model, uint32_t TextureHundle, Vector3 Pos, Model* mahoujin_model) {
	assert(model);

	Model_ = model;
	TextureHundle_ = TextureHundle;

	WorldTransform_.Initialize();
	WorldTransform_.translation_ = Pos;
	float scale = 2.0f;
	WorldTransform_.scale_ = {scale, scale, scale};
	WorldTransform_.rotation_ = {-1.55f,-3.15f,0.0f};
	Input_ = Input::GetInstance();

	ReticleWorldTransform_.Initialize();

	SetCollisionAttribute(kCollisionAttributePlayer);

	SetCollisionMask(~kCollisionAttributePlayer);

	uint32_t textureReticle = TextureManager::Load("CyclamenPink.jpg");

	reticleSprite =
	    Sprite::Create(textureReticle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	HPSprite0 = Sprite::Create(
	    textureReticle, {20.0 + 32.0f, 720.0f - 32.0f - 20.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	HPSprite1 = Sprite::Create(
	    textureReticle, {20.0 + 32.0f + 84.0f, 720.0f - 32.0f - 20.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
	    {0.5f, 0.5f});

	HPSprite2 = Sprite::Create(
	    textureReticle, {20.0 + 32.0f + 84.0f * 2.0f, 720.0f - 32.0f - 20.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
	    {0.5f, 0.5f});

	MahouJinMdel_ = mahoujin_model;

	MahouJinWorldTransform_.Initialize();
	MahouJinWorldTransform_.translation_ = Pos;

	HP = 3;
	invTime = 0;
	deadFlag = false;

}

void Player::Init(Vector3 Pos) {

	WorldTransform_.translation_ = Pos;

}

void Player::Update(ViewProjection viewProjection) {

	XINPUT_STATE joyState;


	if (invTime > 0) {
		invTime--;
	}

	if (HP == 0) {
	
		deadFlag = true;

	}

	Bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {

			delete bullet;
			return true;
		}
		return false;
	});

	// WorldTransform_.TransferMatrix();

	Vector3 Move = {0.0f, 0.0f, 0.0f};


	if (deadFlag == false) {

		const float CHARACTORSPEED = 0.2f;

		if (Mahoujing == false) {
			if (Input_->PushKey(DIK_LEFT)) {
				Move.x -= CHARACTORSPEED;
			} else if (Input_->PushKey(DIK_RIGHT)) {
				Move.x += CHARACTORSPEED;
			}

			if (Input_->PushKey(DIK_UP)) {
				Move.y += CHARACTORSPEED;
			} else if (Input_->PushKey(DIK_DOWN)) {
				Move.y -= CHARACTORSPEED;
			}
		}
			if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Mahoujing == false) {
				Move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * CHARACTORSPEED;
				Move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * CHARACTORSPEED;
			}
			}

		MahouJin(joyState);
		{
			/*Matrix4x4 ScaleMatrix = MakeScaleMatrix(WorldTransform_.scale_);

			Matrix4x4 RotateMatrixX = MakeRotateXmatrix(WorldTransform_.rotation_.x);
			Matrix4x4 RotateMatrixY = MakeRotateYmatrix(WorldTransform_.rotation_.y);
			Matrix4x4 RotateMatrixZ = MakeRotateZmatrix(WorldTransform_.rotation_.z);
			Matrix4x4 RotateMatrixXYZ = Multiply(RotateMatrixX, Multiply(RotateMatrixY,
			RotateMatrixZ));

			Matrix4x4 TranslationMatrix = MakeTransl0-ateMatrix(WorldTransform_.translation_);*/
		}

		//Rotate();
	} else {
		
		Move = { 0.0f,-0.05f,-0.2f};
	
	}
	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Move);

	/*WorldTransform_.matWorld_ = MakeAffineMatrix(
	    WorldTransform_.scale_, WorldTransform_.rotation_, WorldTransform_.translation_);*/

	WorldTransform_.translation_.x =
	    std::clamp(WorldTransform_.translation_.x, -MOVELIMITX, MOVELIMITX);

	WorldTransform_.translation_.y =
	    std::clamp(WorldTransform_.translation_.y, -MOVELIMITY, MOVELIMITY);

	WorldTransform_.UpdateMatrix();

	for (PlayerBullet* bullet : Bullets_) {

		bullet->Update();
	}

	{

		/*WorldTransform_.translation_.x =
		    std::clamp(WorldTransform_.translation_.x, -MOVELIMITX, MOVELIMITX);

		WorldTransform_.translation_.y =
		    std::clamp(WorldTransform_.translation_.y, -MOVELIMITY, MOVELIMITY);

		ImGui::Begin("Player");
		float DebugPos[3] = {
		    WorldTransform_.translation_.x, WorldTransform_.translation_.y,
		    WorldTransform_.translation_.z};
		ImGui::SliderFloat3("Pos", DebugPos, -MOVELIMITX, MOVELIMITX);
		ImGui::End();*/

		// WorldTransform_.translation_ = {DebugPos[0], DebugPos[1], DebugPos[2]};

		// Bullet_ != nullptr;

		/*const float kDistancePlayerTo3DReticle = 150.0f;

		Vector3 offset = {0, 0, 1.0f};

		offset = TransforNormal(offset, WorldTransform_.matWorld_);

		offset = Multiply(kDistancePlayerTo3DReticle, Normalize(offset));

		ReticleWorldTransform_.translation_ = Add(WorldTransform_.translation_, offset);
		ReticleWorldTransform_.UpdateMatrix();

		Vector3 positionReticle;

		positionReticle.x = ReticleWorldTransform_.matWorld_.m[3][0];
		positionReticle.y = ReticleWorldTransform_.matWorld_.m[3][1];
		positionReticle.z = ReticleWorldTransform_.matWorld_.m[3][2];

		Matrix4x4 matViewport =
		    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

		Matrix4x4 matViewProjectionViewPort =
		    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

		positionReticle = Transform(positionReticle, matViewProjectionViewPort);

		reticleSprite->SetPosition(Vector2(positionReticle.x, positionReticle.y));*/

		// POINT mousePosition;

		// GetCursorPos(&mousePosition);

		// HWND hwnd = WinApp::GetInstance()->GetHwnd();
		// ScreenToClient(hwnd, &mousePosition);

		///*Vector2 spritePosition = reticleSprite->GetPosition();

		// if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		//
		//	spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		//	spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		//
		//	reticleSprite->SetPosition(spritePosition);
		// }*/

		// reticleSprite->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));

		// Matrix4x4 matViewport =
		//     MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
		// Matrix4x4 matVPV =
		//     Multiply(Multiply(viewProjection.matView, viewProjection.matProjection),
		//     matViewport);

		// Matrix4x4 matInverseVPV = Inverse(matVPV);

		// Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0);
		// Vector3 posFar = Vector3((float)mousePosition.x, (float)mousePosition.y, 1);

		// posNear = Transform(posNear, matInverseVPV);
		// posFar = Transform(posFar, matInverseVPV);

		// Vector3 mouseDirection = Subtract(posFar, posNear);
		// mouseDirection = Normalize(mouseDirection);

		// const float kDistanceTestObject = 100.0f;

		// ReticleWorldTransform_.translation_ =
		//     Add(posNear, Multiply(kDistanceTestObject, mouseDirection));

		//ReticleWorldTransform_.matWorld_ = MakeAffineMatrix(
		//    ReticleWorldTransform_.scale_, ReticleWorldTransform_.rotation_,
		//    ReticleWorldTransform_.translation_);

		//WorldTransform_.UpdateMatrix();

		//ImGui::Begin("Player");
		//// ImGui::Text("2DReticle:(%f,%f)", mousePosition.x, mousePosition.y);
		//// ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
		//// ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
		//ImGui::Text(
		//    "3DReticle:(%+.2f,%+.2f,%+.2f)", ReticleWorldTransform_.translation_.x,
		//    ReticleWorldTransform_.translation_.y, ReticleWorldTransform_.translation_.z);

		//ImGui::DragFloat3("Pos", &MahouJinWorldTransform_.translation_.x, 0.01f);
		//ImGui::End();
	}
}

void Player::Rotate() {

	const float ROTSPEED = 0.05f;

	if (Input_->PushKey(DIK_A)) {
		WorldTransform_.rotation_.x -= ROTSPEED;
	} else if (Input_->PushKey(DIK_D)) {
		WorldTransform_.rotation_.x += ROTSPEED;
	}

	if (Input_->PushKey(DIK_F)) {
		WorldTransform_.rotation_.y -= ROTSPEED;
	} else if (Input_->PushKey(DIK_H)) {
		WorldTransform_.rotation_.y += ROTSPEED;
	}

	if (Input_->PushKey(DIK_J)) {
		WorldTransform_.rotation_.z -= ROTSPEED;
	} else if (Input_->PushKey(DIK_K)) {
		WorldTransform_.rotation_.z += ROTSPEED;
	}

	ImGui::Begin("Player");
	ImGui::Text("%f", WorldTransform_.rotation_.x);
	ImGui::Text("%f", WorldTransform_.rotation_.y);
	ImGui::Text("%f", WorldTransform_.rotation_.z);
	ImGui::End();
}

void Player::Attack() {

	/*if (Input_->TriggerKey(DIK_SPACE)) {

		const float BULEETSPEED = 1.0f;
		Vector3 velocity(0, 0, BULEETSPEED);

		velocity = Subtract(ReticleWorldTransform_.translation_,WorldTransform_.translation_);
		velocity = Multiply(BULEETSPEED, Normalize(velocity));

		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(Model_, GetWorldPosition(), velocity);

		Bullets_.push_back(newBullet);
	}*/

	
	/*XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	
	}*/

	//if (Input_->TriggerKey(DIK_SPACE)) {
		//MahouJinWorldTransform_.translation_ = WorldTransform_.translation_;
	//}
	
	
	/*	const float BULEETSPEED = 1.0f;
		Vector3 velocity(0, 0, BULEETSPEED);

		velocity = Subtract(ReticleWorldTransform_.translation_, WorldTransform_.translation_);
		velocity = Multiply(BULEETSPEED, Normalize(velocity));

		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(MahouJinMdel_, GetWorldPosition(), velocity);

		Bullets_.push_back(newBullet);*/
	

}

void Player::Draw(ViewProjection ViewProjection) {

	for (PlayerBullet* bullet : Bullets_) {

		bullet->Draw(ViewProjection);
	}

	if (invTime % 5 > 2 || invTime == 0) {

		Model_->Draw(WorldTransform_, ViewProjection);
	}

	if (MahoujinOn == true) {

		MahouJinMdel_->Draw(MahouJinWorldTransform_, ViewProjection);
	} 
	// Model_->Draw(ReticleWorldTransform_, ViewProjection, TextureHundle_);
}

void Player::DrawUI() { //reticleSprite->Draw(); 

	if (HP > 0) {
		HPSprite0->Draw();
	}

	if (HP > 1) {
		HPSprite1->Draw();
	}

	if (HP > 2) {
		HPSprite2->Draw();
	}
}

Vector3 Player::GetWorldPosition() {

	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}

void Player::OnCollision() {

	if (invTime <= 0) {

		HP--;

		invTime = 120;
	}

}

void Player::SetParent(const WorldTransform* parent) {
	assert(parent != nullptr);
	WorldTransform_.parent_ = parent;
	ReticleWorldTransform_.parent_ = parent;
	MahouJinWorldTransform_.parent_ = parent;
}

Vector3 Player::GetMahouJinPos() {
	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = MahouJinWorldTransform_.matWorld_.m[3][0];
	WorldPos.y = MahouJinWorldTransform_.matWorld_.m[3][1];
	WorldPos.z = MahouJinWorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}

void Player::MahouJin(XINPUT_STATE joyState_) {
	OshitazoGomi = false;
	if (((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && shine == 0) ||
	    Input_->TriggerKey(DIK_SPACE)) {
		// Attack();

		MahouJinWorldTransform_.scale_ = {0.5f,0.5f,1.0f};

		MahouJinWorldTransform_.translation_ = WorldTransform_.translation_;
		OshitazoGomi = true;
		MahoujinOn = true;
	}
		
	float MAXSIZE = 10.0f;

	
	int kuso = 0;

		if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		kuso = 1;
		}

	if ((kuso == 1 && shine == 1)||
	    Input_->PushKey(DIK_SPACE)) {


		Vector3 scalePlus = {0.1f, 0.1f, 0.0f};

		if (MAXSIZE > MahouJinWorldTransform_.scale_.x) {

			MahouJinWorldTransform_.scale_ = Add(MahouJinWorldTransform_.scale_, scalePlus);
		}

		if (MAXSIZE <= MahouJinWorldTransform_.scale_.x) {
			MahouJinWorldTransform_.scale_ = {MAXSIZE, MAXSIZE, 1.0f};
		}


		Vector3 scalePlusPos = {0.0f, 0.0f, 0.0f};

		MahouJinWorldTransform_.translation_ =
		    Add(MahouJinWorldTransform_.translation_, scalePlusPos);
		Mahoujing = true;

	} else {
		Mahoujing = false;
	}
	
	
	MahouJinWorldTransform_.UpdateMatrix();
	
	if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ||
	    Input_->TriggerKey(DIK_SPACE)) {
	}else{

		if (MahoujinOn == true) {
		
			if (Mahoujing == false) {

				if (Charging == false) {

					const float BULEETSPEED = 1.0f;
					Vector3 velocity(0, 0, BULEETSPEED);

					// velocity = Subtract(ReticleWorldTransform_.translation_,
					// MahouJinWorldTransform_.translation_); velocity = Multiply(BULEETSPEED,
					// Normalize(velocity));

					PlayerBullet* newBullet = new PlayerBullet();

					Vector3 ShotPos = {0.0f, 0.0f, 0.0f};

					ShotPos.x = MahouJinWorldTransform_.matWorld_.m[3][0];
					ShotPos.y = MahouJinWorldTransform_.matWorld_.m[3][1];
					ShotPos.z = MahouJinWorldTransform_.matWorld_.m[3][2];

					newBullet->Initialize(MahouJinMdel_, ShotPos, velocity);
					newBullet->SetMahouJinScale(MahouJinWorldTransform_.scale_.x);
					newBullet->SetPlayer(this);

					Bullets_.push_back(newBullet);

					Charging = true;
				}
			}
		}
	}

	shine = kuso;
}
