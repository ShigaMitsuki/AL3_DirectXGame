#include "GameScene.h"
#include "TextureManager.h"
#include "ImGui.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {

	uint32_t blackTex = TextureManager::Load("PaefectBlack.png");

	Black = Sprite::Create(blackTex, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Black->SetSize({blackSize, blackSize});

	uint32_t GameOverTex = TextureManager::Load("GameOver.png");

	GameOver =
	    Sprite::Create(GameOverTex, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	uint32_t GameClearTex = TextureManager::Load("GameClear.png");

	GameClear =
	    Sprite::Create(GameClearTex, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	uint32_t TutorialTex = TextureManager::Load("Tule.png");

	Tutorial =
	    Sprite::Create(TutorialTex, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

}

GameScene::~GameScene() {
	delete Model_;
	delete Player_;
	delete DebugCamera_;
	delete modelSkyDome;
	delete Black;
	delete GameOver;
	delete GameClear;
	delete Tutorial;

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
	ViewProjection_.farZ = 1000000;

	Player_ = new Player();

	Vector3 PlayerPosition = {0.0f,-4.0f, 20.0f};

	mahouJinModel = Model::CreateFromOBJ("MahouJin", true);

	mahoModel = Model::CreateFromOBJ("Maho", true);

	enemyModel = Model::CreateFromOBJ("enemy", true);

	Player_->Initialize(mahoModel, PlayerTexture, PlayerPosition, mahouJinModel);

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
	enemyPopCommands.str("");

	enemyPopCommands.clear(std::stringstream::goodbit);
	LoadEnemyPopData();

	GameOverFlag = false;
	GameClearFlag = false;

	StatFlag = false;
}

void GameScene::Update() {
	// 自キャラ更新

	XINPUT_STATE joyState;

	SkyDome_->Update();

	if (owarimade > owari && resetTime == 0) {
		resetTime = 1;
		GameClearFlag = true;
	}

	if (StatFlag == true) {
		owarimade++;
	}

	if (Player_->GetDeadFlag() == true && resetTime == 0) {
		resetTime = 1;
		GameOverFlag = true;
		
	}

	/*ImGui::Begin("Player");
	ImGui::Text("%d", owarimade);
	ImGui::End();*/

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if ((float)joyState.Gamepad.sThumbLX || (float)joyState.Gamepad.sThumbLY) {

			StatFlag = true;
		}
	}

	if (resetTime > 0) {

		if (resetTime == 240) {


			Reset();
		}

		if (resetTime >= 121 && resetTime < 301) {
			
			if (resetTime <= 180) {

				blackSize = (float)(resetTime - 120.0f) /60.0f;
			}
		} else if (resetTime >= 301) {

			if (resetTime <= 360) {

				blackSize = 1.0f - ((float)(resetTime - 300.0f) / 60.0f);
			} 
		}

		resetTime++;

		 if (resetTime > 360) {
			resetTime = 0;
			owarimade = 0;
			blackSize = 0.0f;
		 }
	}

	if (resetTime < 120 || resetTime > 300) {
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

		if (StatFlag == true) {

			UpdateEnemyPopCommands();
		}

		for (Enemy* enemy : Enemy_) {

			enemy->Update();

			
		}

		Enemy_.remove_if([](Enemy* enemy) {
			if (enemy->isDead()) {
				delete enemy;
				return true;
			}
			return false;
		});

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

		const std::list<PlayerBullet*>& PlayerBullets = Player_->GetBullets();

		for (Enemy* enemy : Enemy_) {
			for (PlayerBullet* bullet : PlayerBullets) {

				Vector3 enemypos = enemy->GetWorldPosition();
				Vector3 bulletpos = bullet->GetWorldPosition();

				if (fabs(bulletpos.z - enemypos.z) < 1.0f &&
				    Distance(enemypos, bulletpos) < enemy->GetScale() + bullet->GetScale()) {
					if (bullet->GetShotFlag()) {

						bullet->OnCollision();
						enemy->OnCollision();
					}
				}
			}
		}

		for (Enemy* enemy : Enemy_) {
			Vector3 posA = enemy->GetWorldPosition();
			Vector3 posB = Player_->GetWorldPosition();

			if (Distance(posA, posB) < 1.0f + enemy->GetScale()) {
				Player_->OnCollision();
			}
		}

		for (EnemyBullet* bullet : enemyBullets_) {
			Vector3 posA = bullet->GetWorldPosition();
			Vector3 posB = Player_->GetWorldPosition();

			if (Distance(posA, posB) < 1.0f ) {
				Player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}

	//CollisionManager_.Clear();

	//for (Enemy* enemy : Enemy_) {

	//	enemy;

	//	if (Player_->) {
	//	
	//	}

	//	//CollisionManager_.CheckAllCollisions(Player_, enemy, this);
	//}
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

	Tutorial->Draw();

	Player_->DrawUI();
	
	if (GameClearFlag == true) {

		GameClear->Draw();
	}

	if (GameOverFlag == true) {

		GameOver->Draw();
	}

	Black->SetSize({blackSize * 1280.0f, blackSize * 720.0f});
	Black->Draw();

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

			getline(line_stream, word, ',');
			int type = (int)std::atof(word.c_str());

			Enemy* newEnemy_ = new Enemy();
			newEnemy_->SetPlayer(Player_);
			newEnemy_->SetGameScene(this);
			newEnemy_->Initialize(enemyModel, {x, y, z}, type);

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

void GameScene::Reset() {

	waitFlag = false;
	waitTimer = 0;

	Initialize();

	Enemy_.remove_if([](Enemy* enemy) {
		delete enemy;
		return true;
	});

	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		delete bullet;
		return true;
	});

}
