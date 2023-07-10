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
}

void Player::Initialize(Model* model, uint32_t TextureHundle, Vector3 Pos) {
	assert(model);

	Model_ = model;
	TextureHundle_ = TextureHundle;

	WorldTransform_.Initialize();
	WorldTransform_.translation_ = Pos;
	Input_ = Input::GetInstance();

	ReticleWorldTransform_.Initialize();

	SetCollisionAttribute(kCollisionAttributePlayer);

	SetCollisionMask(~kCollisionAttributePlayer);

	uint32_t textureReticle = TextureManager::Load("CyclamenPink.jpg");

	reticleSprite =
	    Sprite::Create(textureReticle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
}

void Player::Update(ViewProjection viewProjection) {

	XINPUT_STATE joyState;

	Bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {

			delete bullet;
			return true;
		}
		return false;
	});

	// WorldTransform_.TransferMatrix();

	Vector3 Move = {0.0f, 0.0f, 0.0f};

	const float CHARACTORSPEED = 0.2f;

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


	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		Move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * CHARACTORSPEED;
		Move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * CHARACTORSPEED;
	}

	/*Matrix4x4 ScaleMatrix = MakeScaleMatrix(WorldTransform_.scale_);

	Matrix4x4 RotateMatrixX = MakeRotateXmatrix(WorldTransform_.rotation_.x);
	Matrix4x4 RotateMatrixY = MakeRotateYmatrix(WorldTransform_.rotation_.y);
	Matrix4x4 RotateMatrixZ = MakeRotateZmatrix(WorldTransform_.rotation_.z);
	Matrix4x4 RotateMatrixXYZ = Multiply(RotateMatrixX, Multiply(RotateMatrixY, RotateMatrixZ));

	Matrix4x4 TranslationMatrix = MakeTransl0-ateMatrix(WorldTransform_.translation_);*/

	Rotate();

	WorldTransform_.translation_ = Add(WorldTransform_.translation_, Move);

	/*WorldTransform_.matWorld_ = MakeAffineMatrix(
	    WorldTransform_.scale_, WorldTransform_.rotation_, WorldTransform_.translation_);*/

	WorldTransform_.UpdateMatrix();

	WorldTransform_.translation_.x =
	    std::clamp(WorldTransform_.translation_.x, -MOVELIMITX, MOVELIMITX);

	WorldTransform_.translation_.y =
	    std::clamp(WorldTransform_.translation_.y, -MOVELIMITY, MOVELIMITY);

	ImGui::Begin("Player");
	float DebugPos[3] = {
	    WorldTransform_.translation_.x, WorldTransform_.translation_.y,
	    WorldTransform_.translation_.z};
	ImGui::SliderFloat3("Pos", DebugPos, -MOVELIMITX, MOVELIMITX);
	ImGui::End();

	// WorldTransform_.translation_ = {DebugPos[0], DebugPos[1], DebugPos[2]};
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		Attack();
	}
	for (PlayerBullet* bullet : Bullets_) {

		bullet->Update();
	}

	// Bullet_ != nullptr;

	/*const float kDistancePlayerTo3DReticle = 50.0f;

	Vector3 offset = {0, 0, 1.0f};

	offset = TransforNormal(offset, WorldTransform_.matWorld_);

	offset = Multiply(kDistancePlayerTo3DReticle, Normalize(offset));

	ReticleWorldTransform_.translation_ = Add(WorldTransform_.translation_, offset);
	ReticleWorldTransform_.UpdateMatrix();

	Vector3 positionReticle;

	positionReticle.x = ReticleWorldTransform_.matWorld_.m[3][0];
	positionReticle.y = ReticleWorldTransform_.matWorld_.m[3][1];
	positionReticle.z = ReticleWorldTransform_.matWorld_.m[3][2];

	Matrix4x4 matViewport = MakeViewportMatrix(0,0,WinApp::kWindowWidth,WinApp::kWindowHeight,0,1);
	
	

	Matrix4x4 matViewProjectionViewPort =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

	positionReticle = Transform(positionReticle, matViewProjectionViewPort);

	reticleSprite->SetPosition(Vector2(positionReticle.x, positionReticle.y));*/

	//POINT mousePosition;

	/*GetCursorPos(&mousePosition);

	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);*/

	Vector2 spritePosition = reticleSprite->GetPosition();

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	
		spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		
		reticleSprite->SetPosition(spritePosition);
	}

	//reticleSprite->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));

	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matVPV =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

	Matrix4x4 matInverseVPV = Inverse(matVPV);

	Vector3 posNear = Vector3((float)spritePosition.x, (float)spritePosition.y, 0);
	Vector3 posFar = Vector3((float)spritePosition.x, (float)spritePosition.y, 1);

	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalize(mouseDirection);

	const float kDistanceTestObject = 100.0f;

	ReticleWorldTransform_.translation_ =
	    Add(posNear, Multiply(kDistanceTestObject, mouseDirection));

	ReticleWorldTransform_.matWorld_ = MakeAffineMatrix(
		ReticleWorldTransform_.scale_,
		ReticleWorldTransform_.rotation_,
		ReticleWorldTransform_.translation_);

	WorldTransform_.UpdateMatrix();


	ImGui::Begin("Player");
	ImGui::Text("2DReticle:(%f,%f)", spritePosition.x, spritePosition.y);
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DReticle:(%+.2f,%+.2f,%+.2f)", ReticleWorldTransform_.translation_.x,
	    ReticleWorldTransform_.translation_.y, ReticleWorldTransform_.translation_.z);
	ImGui::End();

}

void Player::Rotate() {

	const float ROTSPEED = 0.05f;

	if (Input_->PushKey(DIK_A)) {
		WorldTransform_.rotation_.y -= ROTSPEED;
	} else if (Input_->PushKey(DIK_D)) {
		WorldTransform_.rotation_.y += ROTSPEED;
	}
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

	
	
		const float BULEETSPEED = 1.0f;
		Vector3 velocity(0, 0, BULEETSPEED);

		velocity = Subtract(ReticleWorldTransform_.translation_, WorldTransform_.translation_);
		velocity = Multiply(BULEETSPEED, Normalize(velocity));

		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(Model_, GetWorldPosition(), velocity);

		Bullets_.push_back(newBullet);
	

}

void Player::Draw(ViewProjection ViewProjection) {

	for (PlayerBullet* bullet : Bullets_) {

		bullet->Draw(ViewProjection);
	}

	Model_->Draw(WorldTransform_, ViewProjection, TextureHundle_);
	//Model_->Draw(ReticleWorldTransform_, ViewProjection, TextureHundle_);
}

void Player::DrawUI() { reticleSprite->Draw(); }

Vector3 Player::GetWorldPosition() {

	Vector3 WorldPos = {0.0f, 0.0f, 0.0f};

	WorldPos.x = WorldTransform_.matWorld_.m[3][0];
	WorldPos.y = WorldTransform_.matWorld_.m[3][1];
	WorldPos.z = WorldTransform_.matWorld_.m[3][2];

	return WorldPos;
}

void Player::OnCollision() {}

void Player::SetParent(const WorldTransform* parent) {
	assert(parent != nullptr);
	WorldTransform_.parent_ = parent;
	ReticleWorldTransform_.parent_ = parent;
}
