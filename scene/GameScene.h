#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Vector3.h"
#include "AxisIndicator.h"
#include "Enemy.h"
#include "CollisionManager.h"
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

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用

	////////自キャラ
	//テクスチャハンドル
	uint32_t PlayerTexture = 0;

	//3d
	Model* Model_ = nullptr;

	//TransForm
	//WorldTransform WorldTransform_;
	ViewProjection ViewProjection_;

	Player* Player_ = nullptr;
	Enemy* Enemy_ = nullptr;

	bool IsDebugCameraActive_ = true;

	DebugCamera* DebugCamera_ = nullptr;

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

	CollisionManager CollisionManager_;

	/// </summary>
};
