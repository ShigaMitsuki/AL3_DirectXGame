#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete Model_;
	delete Player_;
	delete DebugCamera_;
	delete Enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	////自キャラ
	PlayerTexture = TextureManager::Load("AzaleaPink.png");
	Model_ = Model::Create();

	//WorldTransform_.Initialize();
	ViewProjection_.Initialize();

	Player_ = new Player();

	Player_->Initialize(Model_, PlayerTexture);

	DebugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&ViewProjection_);

	
	Enemy_ = new Enemy();
	Enemy_->SetPlayer(Player_);
	Enemy_->Initialize(Model_, {10,0,200});
	
	
}

void GameScene::Update() { 
	//自キャラ更新
	Player_->Update();
	if (IsDebugCameraActive_) {
		DebugCamera_->Update();
		
		ViewProjection_.matView = DebugCamera_->GetViewProjection().matView;
		ViewProjection_.matProjection = DebugCamera_->GetViewProjection().matProjection;
		
		ViewProjection_.TransferMatrix();
	} else {
		ViewProjection_.UpdateMatrix();
	}

	if (Enemy_ != nullptr) {
		Enemy_->Update();
	}

	CollisionManager_.Clear();
	CollisionManager_.CheckAllCollisions(Player_,Enemy_);
	//CheckAllCollisions();
	//デバッグ時のみ有効
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_1)) {
		if (IsDebugCameraActive_) {
			IsDebugCameraActive_ = false;
		} else {
			IsDebugCameraActive_ = true;
		}
	}
	#endif
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///自kyら
	Player_->Draw(ViewProjection_);
	if (Enemy_ != nullptr) {
		Enemy_->Draw(ViewProjection_);
	}
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}