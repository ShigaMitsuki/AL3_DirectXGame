#include "GameScene.h"
#include "TextureManager.h"
#include "ImGui.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete Model_;
	delete Player_;
	delete DebugCamera_;
	delete modelSkyDome;

	for (EnemyBullet* bullet : enemyBullets_) {

		delete bullet;
	}

	for (Enemy* enemy: Enemy_) {

		delete enemy;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	////自キャラ
	PlayerTexture = TextureManager::Load("AzaleaPink.png");
	Model_ = Model::Create();

	TextureManager::Load("CyclamenPink.jpg");

	//WorldTransform_.Initialize();

	ViewProjection_.Initialize();
	ViewProjection_.farZ = 10000;

	Player_ = new Player();

	Vector3 PlayerPosition = {0.0f,-4.0f, 20.0f};
	Player_->Initialize(Model_, PlayerTexture, PlayerPosition);

	DebugCamera_ = new DebugCamera(1280, 720);

	DebugCamera_->SetFarZ(10000);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&ViewProjection_);

	
	/*Enemy* newEnemy_ = new Enemy();
	newEnemy_->SetPlayer(Player_);
	newEnemy_->SetGameScene(this);
	newEnemy_->Initialize(Model_, {10, 0, 200});

	Enemy_.push_back(newEnemy_);*/

	//Enemy* newEnemy = new Enemy();

	modelSkyDome = Model::CreateFromOBJ("SkyDome", true);
	
	SkyDome_ = new SkyDome();
	SkyDome_->Initialize(modelSkyDome);

	RailCamera_ = new RailCamera();
	RailCamera_->Initialize(ViewProjection_.translation_, {0.0f, 0.0f, 0.0f});
	//assert(&RailCamera_->GetWorldTransform());
	Player_->SetParent(&RailCamera_->GetWorldTransform());

	//&RailCamera_->GetWorldTransform();

	LoadEnemyPopData();
}

void GameScene::Update() { 
	//自キャラ更新
	Player_->Update(ViewProjection_);

	if (IsDebugCameraActive_) {
		DebugCamera_->Update();
		
		ViewProjection_.matView = DebugCamera_->GetViewProjection().matView;
		ViewProjection_.matProjection = DebugCamera_->GetViewProjection().matProjection;
		
		ViewProjection_.TransferMatrix();
	} else {
		RailCamera_->Update();

		ViewProjection_.matView = RailCamera_->GetViewProjection().matView;
		ViewProjection_.matProjection = RailCamera_->GetViewProjection().matProjection;
		ViewProjection_.TransferMatrix();

	}

	UpdateEnemyPopCommands();

	for (Enemy* enemy : Enemy_) {

		enemy->Update();

		if (enemy->isDead()) {
			delete enemy;
		}
	}

	

	
	for (EnemyBullet* bullet : enemyBullets_) {

		bullet->Update();
		
	}

	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {

			delete bullet;
			return true;
		}
		return false;
	});
	

	CollisionManager_.Clear();

	for (Enemy* enemy : Enemy_) {
		CollisionManager_.CheckAllCollisions(Player_, enemy, this);
	}
	//CheckAllCollisions();
	// 

	//RailCamera_.Update();
	//RailCamera_.Update();
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

	SkyDome_->Draw(ViewProjection_);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///自kyら
	Player_->Draw(ViewProjection_);

	for (Enemy* enemy : Enemy_) {
		enemy->Draw(ViewProjection_);
	}

	for (EnemyBullet* bullet : enemyBullets_) {

		bullet->Draw(ViewProjection_);
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

	Player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {

	enemyBullets_.push_back(enemyBullet);

}

void GameScene::LoadEnemyPopData() {

	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();


}

void GameScene::UpdateEnemyPopCommands() {
	
	if (waitFlag) {

		waitTimer--;
		if (waitTimer <= 0) {
			waitFlag = false;
		}
		
		return;
	}

	std::string line;

	while (getline(enemyPopCommands, line)) {
	
		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream, word, ',');
		
		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			Enemy* newEnemy_ = new Enemy();
			newEnemy_->SetPlayer(Player_);
			newEnemy_->SetGameScene(this);
			newEnemy_->Initialize(Model_, {x, y, z});

			Enemy_.push_back(newEnemy_);
		} else if (word.find("WAIT") == 0) {
			
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());

			 waitFlag = true;
			waitTimer = waitTime;

			break;
		}
	}

}
