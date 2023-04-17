#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "DebugCamera.h"
#include "AxisIndicator.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	 
	//テクスチャ
	uint32_t TextureHandle_ = 0;

	// 3Dモデル
	Model* Model_ = nullptr;

	//サウンドデータ
	uint32_t SoundDataHandle_ = 0;

	//音声再生ハンドル
	uint32_t VoiceHundle_ = 0;

	//スプライト
	Sprite* Sprite_ = nullptr;

	int Mode = 0;

	//インプット
	Input* Input_ = nullptr;

	// ImGuiの値
	float InputFloat3[3] = {0.0f, 0.0f, 0.0f};

	//デバッグカメラ
	DebugCamera* DebugCamera_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform WorldTransform_;
	//ビュープロジェクション
	ViewProjection ViewProjection_;

	/// </summary>
};
