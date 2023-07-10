#pragma once

#include "Audio.h"
#include "AxisIndicator.h"
#include "CollisionManager.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "RailCamera.h"
#include "SafeDelete.h"
#include "SkyDome.h"
#include "Sprite.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <sstream>

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

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	const std::list<EnemyBullet*>& GetBullets() { return enemyBullets_; };

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用

	////////自キャラ
	// テクスチャハンドル
	uint32_t PlayerTexture = 0;

	// 3d
	Model* Model_ = nullptr;

	// TransForm
	// WorldTransform WorldTransform_;
	ViewProjection ViewProjection_;

	Player* Player_ = nullptr;
	std::list<Enemy*> Enemy_;
	SkyDome* SkyDome_ = nullptr;

	bool IsDebugCameraActive_ = false;

	DebugCamera* DebugCamera_ = nullptr;

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

	CollisionManager CollisionManager_;

	Model* modelSkyDome = nullptr;

	RailCamera* RailCamera_ = nullptr;

	std::list<EnemyBullet*> enemyBullets_;

	std::stringstream enemyPopCommands;

	bool waitFlag = false;

	int waitTimer = 0;

	/// </summary>
};
