#include "GameScene.h"
#include "TextureManager.h"

#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete Sprite_;
	delete Model_;
	delete DebugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャ読み込み
	TextureHandle_ = TextureManager::Load("mario.jpg");

	//サウンド読み込み[
	SoundDataHandle_ = audio_->LoadWave("mokugyo.wav");

	//スプライト生成
	Sprite_ = Sprite::Create(TextureHandle_, {100, 50});

	Input_ = Input::GetInstance();

	//3Dモデル生成
	Model_ = Model::Create();

	// ワールドトランスフォーム初期化
	WorldTransform_.Initialize();
	// ビュープロジェクション初期化
	ViewProjection_.Initialize();

	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&ViewProjection_);
	
	// デバッグカメラの生成
	DebugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&DebugCamera_->GetViewProjection());
}

void GameScene::Update() {

	ImGui::Begin("Check");
	ImGui::Text("[Z] key -> Next Mode");
	ImGui::End();

	switch (Mode) {
	case 1:
		// 座標取得
		Vector2 Position = Sprite_->GetPosition();

		Position.x += 2.0f;
		Position.y += 1.0f;
		// 移動を反映
		Sprite_->SetPosition(Position);
		break;
	case 4:

		if (Input_->TriggerKey(DIK_SPACE)) {
			audio_->StopWave(VoiceHundle_);
		}
		break;
	case 5:
		ImGui::Begin("Debug1");
		ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
		ImGui::End();
		

		ImGui::Begin("Debug2");
		ImGui::InputFloat3("InputFloat3",InputFloat3);

		ImGui::SliderFloat3("SliderFloat3", InputFloat3,0.0f,1.0f);
		ImGui::End();

		ImGui::ShowDemoWindow();
		break;
	}

	if (Input_->TriggerKey(DIK_Z)) {
		Mode += 1;

		if (Mode > 6) {
			Mode = 0;
		}
		switch (Mode) {
		case 3:
			SoundDataHandle_ = audio_->LoadWave("fanfare.wav");
			audio_->PlayWave(SoundDataHandle_);

			break;
		case 4:
			SoundDataHandle_ = audio_->LoadWave("mokugyo.wav");
			VoiceHundle_ = audio_->PlayWave(SoundDataHandle_, true);
			
			break;
		case 5:
			audio_->StopWave(VoiceHundle_);
			break;
		}
	}

	DebugCamera_->Update();
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

	

	switch (Mode) {
	case 0:
	case 1:
		Sprite_->Draw();
		break;
	}

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
	/// </summary>

	switch (Mode) {
	case 2:
		Model_->Draw(WorldTransform_, DebugCamera_->GetViewProjection(), TextureHandle_);
		break;
	}

	// 3Dオブジェクト描画後処理

	switch (Mode) {
	case 6:
		PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
	}
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
