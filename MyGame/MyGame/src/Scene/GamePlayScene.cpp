#include "GamePlayScene.h"
#include"../Graphic/Model.h"
#include"../Camera/Camera.h"
#include"../Actor/ActorGroup.h"
#include"../Actor/Player/Player.h"
#include"../Field/Field.h"
#include"../Actor/Body/BoundingCapsule.h"
#include"../Camera/CameraActor.h"
#include"../Camera/OverLookingCamera.h"
#include<memory>
#include"../Actor/Enemy/BaseEnemy.h"
#include"../Actor/Enemy/NormalEnemy.h"
#include"../Actor/Enemy/Enemy_Power.h"
#include"../Actor/Enemy/Enemy_Round/Enemy_Round.h"
#include"../Actor/Enemy/Enemy_Quick/Enemy_Quick.h"
#include"../Actor/Enemy/Enemy_Rival/Enemy_Rival.h"
#include"../Actor/Enemy/Enemy_Notice/Enemy_Notice.h"

#include"../UI/UITemplate.h"
#include<EffekseerForDXLib.h>
#include"../Actor/Judge/Judge_NPC/Judge_NPC.h"
#include"../Actor/Judge/Judgement_SpotLight/Judgement_SpotLight.h"
#include"../UI/UIInclude.h"
#include"../Input/InputChecker.h"
#include"../Input/Keyboard.h"
#include"../Game/Time.h"
#include"../DataManager/DataManager.h"
#include"../Sound/TempoManager.h"
#include"../Fade/FadePanel.h"
#include "../UI/EndUI.h"
#include "../UI/Song_Title_UI.h"
#include"../Graphic/EffekseerManager.h"

//ゲームの時間
static const float gameTime = 5.0f;
static const std::vector<std::tuple<BGM_ID, float, int, int, bool, int>> stageList{//楽曲ID,BPM,拍数,巡回エネミーの数,ライバルの有無,音量
	std::make_tuple(BGM_ID::STAGE1_BGM,156.0f,3,3,false,150),
	std::make_tuple(BGM_ID::STAGE2_BGM,180.0f,3,2,true,255),
	std::make_tuple(BGM_ID::STAGE3_BGM,132.0f,2,3,true,255)
};

//コンストラクタ
GamePlayScene::GamePlayScene() :world_(), /*scoreDisplay_(nullptr),*/ playerEffectDraw_(nullptr), standardLight_(), lightHandle_(), pause_() {
	//更新遷移先の設定
	updateFuncMap_[GamePlayState::Reload] = [&](float deltaTime) {update_Reload(deltaTime); };
	updateFuncMap_[GamePlayState::Start] = [&](float deltaTime) {update_Start(deltaTime); };
	updateFuncMap_[GamePlayState::Play] = [&](float deltaTime) {update_Play(deltaTime); };
	updateFuncMap_[GamePlayState::Pause] = [&](float deltaTime) {update_Pause(deltaTime); };
	updateFuncMap_[GamePlayState::End] = [&](float deltaTime) {update_End(deltaTime); };

}

//開始
void GamePlayScene::start() {
	isStart_ = false;

	Sound::GetInstance().StopBGM();

	stageNum_ = DataManager::GetInstance().getStage();//ステージ番号受け取り
													  //ワールド初期化
	world_.Initialize();
	//シャドウマップがいるか？
	world_.setShadowMap(true, MODEL_ID::STAGE_MODEL);
	pause_.initialize();

	//ライトの設定
	settingLight();

	state_ = GamePlayState::Start;

	std::shared_ptr<Field> field = std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<OverLookingCamera> camera = std::make_shared<OverLookingCamera>(&world_, "Camera", Vector3::Zero);
	world_.addCamera(camera);

	//選手番号
	int playerNumber = 1;
	std::shared_ptr<Player> player = std::make_shared<Player>(&world_, "Player", Vector3::Up*15.0f + Vector3{ 0.0f,0.0f,50.0f }, playerNumber);
	world_.addActor(ActorGroup::PLAYER, player);

	//player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
	//player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	//player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	//
	//player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Half});
	//player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});
	//player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});

	Vector3 pos{ -80.0f,10.0f,-40.0f };
	//playerNumber++;
	//auto enemy = std::make_shared<Enemy_Notice>(&world_, "Enemy", pos, playerNumber);
	//world_.addActor(ActorGroup::ENEMY, enemy);
	//world_.addStepTimeListener(enemy);
	for (int i = 0; i < std::get<3>(stageList[stageNum_-1]); i++) {
		playerNumber++;
		auto enemy = std::make_shared<Enemy_Round>(&world_, "Enemy", pos, playerNumber);
		world_.addActor(ActorGroup::ENEMY, enemy);
		world_.addStepTimeListener(enemy);
		pos += Vector3{ 70.0f,0.0f,30.0f };
	}
	if (std::get<4>(stageList[stageNum_-1])) {
		playerNumber++;
		auto enemy = std::make_shared<Enemy_Rival>(&world_, "Enemy", Vector3::Up*10.0f + Vector3(-30.f, 0.f, 30.f), playerNumber);
		world_.addActor(ActorGroup::ENEMY, enemy);
		world_.addStepTimeListener(enemy);
	}
	//playerNumber++;
	//auto enemy2 = std::make_shared<Enemy_Power>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(70.f, 0.f, -60.f), playerNumber);
	//world_.addActor(ActorGroup::ENEMY, enemy2);
	//playerNumber++;
	//auto enemy3 = std::make_shared<NormalEnemy>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(40.f, 0.f, -20.f), playerNumber);
	//world_.addActor(ActorGroup::ENEMY, enemy3);
	//world_.addStepTimeListener(enemy2);
	//world_.addStepTimeListener(enemy3);

	//world_.addStepTimeListener(player);

	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(-110.0f, 0.0f, 60.0f), Matrix::CreateRotationY(-45.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(110.0f, 0.0f, 60.0f), Matrix::CreateRotationY(45.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(110.0f, 0.0f, -60.0f), Matrix::CreateRotationY(135.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(-110.0f, 0.0f, -60.0f), Matrix::CreateRotationY(-135.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judgement_SpotLight>(&world_, Vector3(0.0f, 2.0f, 0.0f), lightHandle_));
	world_.getCamera()->setTarget(world_.findActor("Player"));
	world_.getCamera()->setFirstPos();

	//楽曲のセット
	world_.getCanChangedTempoManager().setMusic(std::get<0>(stageList[stageNum_ - 1]), std::get<1>(stageList[stageNum_ - 1]), std::get<2>(stageList[stageNum_ - 1]), 4, std::get<5>(stageList[stageNum_ - 1]));

	//UIの設定
	settingUI();

	//スコア表示設定
	//scoreDisplay_.initialize();
	//scoreDisplay_.setScoreManager(&world_.getCanChangedScoreManager());

	//アクター検索を掛けるクラス群の初期化
	world_.FindInitialize();

	//エフェクトの設定
	playerEffectDraw_.Initialize();
	playerEffectDraw_.setPlayerEffectDraw(player.get());

	timeCount_ = 3.0f;
	currentCount_ = (int)std::ceilf(timeCount_) + 1;
}

//更新
void GamePlayScene::update(float deltaTime) {
	//状態更新
	updateFuncMap_[state_](deltaTime);
}

//描画
void GamePlayScene::draw() const {

	world_.draw();

	//for (int i = 1; i < world_.getScoreManager().GetCharacterCount() + 1; i++) {
	//	DebugDraw::DebugDrawFormatString(200, 500 + i * 30, GetColor(255, 255, 255), "%iscore:%i", i, world_.getScoreManager().GetCharacterScore(i));
	//}

	//Time::GetInstance().draw_fps();
	//scoreDisplay_.Score(Vector2(0, 25), 5);

	if (state_ != GamePlayState::Start)playerEffectDraw_.Draw();
	else {
		SetDrawBright(255, 155, 0);
		NumberManager::GetInstance().DrawNumber(Vector2(WINDOW_WIDTH / 2 - 45, WINDOW_HEIGHT / 2 - 70), (int)std::ceilf(timeCount_), 1, FONT_ID::BIG_FONT);
		SetDrawBright(255, 255, 255);
	}

	if (state_ == GamePlayState::Pause)pause_.draw();
}

//終了
void GamePlayScene::end() {
	world_.end();
	//スコアデータをデータマネージャーに渡す
	std::list<ScoreData*> list;
	world_.getCanChangedScoreManager().getScoreDataList(list);
	DataManager::GetInstance().setData(list);

	//scoreDisplay_.finalize();
	//ライトハンドルの全削除
	lightHandle_.deleteLightHandleAll();
	//エフェクトの終了処理
	playerEffectDraw_.finalize();
	EffekseerManager::GetInstance().Stop();
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE();
}

//リトライ更新
void GamePlayScene::update_Reload(float deltaTime) {
	changeState(GamePlayState::Play);
	world_.update_end(deltaTime);
}

//開始更新
void GamePlayScene::update_Start(float deltaTime) {
	timeCount_ -= deltaTime;
	if (timeCount_ <= 0.0f) {
		if (isStart_) {
			if (timeCount_ <= -0.2f) {
				changeState(GamePlayState::Play);
			}
			return;
		}
		Sound::GetInstance().PlaySE(SE_ID::COUNT_FINISH_SE);
		isStart_ = true;
		return;
	}

	if (currentCount_ > (int)std::ceilf(timeCount_)) {
		currentCount_--;
		currentCount_ = max(currentCount_, 0);
		Sound::GetInstance().PlaySE(SE_ID::COUNT_SE);

	}

	world_.update_end(deltaTime);
}

//実行更新
void GamePlayScene::update_Play(float deltaTime) {
	world_.update(deltaTime);

	if (world_.getCanChangedTempoManager().isEnd()) {
		changeState(GamePlayState::End);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		changeState(GamePlayState::Pause);
		return;
	}

	//エフェクト更新
	playerEffectDraw_.Update(deltaTime);
}

//ポーズ更新
void GamePlayScene::update_Pause(float deltaTime) {
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		changeState(GamePlayState::Play);
		return;
	}
	world_.update_end(deltaTime);

	GamePlayState state;
	int p = pause_.update(deltaTime, next_, state);
	if (p == 1) {
		isEnd_ = true;
	}
	else if (p == 2) {
		changeState(state);
	}
}

//終了更新
void GamePlayScene::update_End(float deltaTime) {
	UIPtr p = world_.findUI("EndUI");
	std::shared_ptr<EndUI> endUi = std::static_pointer_cast<EndUI>(p);
	if (endUi->end()) {
		isEnd_ = true;
		next_ = SceneType::SCENE_CLEAR;
	}
	world_.update_end(deltaTime);

}

//状態遷移
void GamePlayScene::changeState(GamePlayState state) {
	if (state_ == state)return;//既にその状態なら遷移しない

							   //状態の終了処理を行う
	switch (state_)
	{
	case Reload:
		break;
	case Start:
		world_.getCanChangedTempoManager().startMusic();//音を再生
		break;
	case Play:
		break;
	case Pause:
		playerEffectDraw_.restartSound();

		world_.restart();
		break;
	case End:
		break;
	default:
		break;
	}

	//状態を変えて
	state_ = state;

	//対応した変更時処理を行う
	switch (state_)
	{
	case Reload:
		end();
		start();
		break;
	case Start:
		break;
	case Play:
		break;
	case Pause:
		playerEffectDraw_.pauseSound();
		world_.pause();
		pause_.start();
		break;
	case End: {
		std::shared_ptr<EndUI> endUI = std::make_shared<EndUI>(&world_.getCanChangedTempoManager(), SCREEN_SIZE / 2);
		world_.addUI(endUI);

		break;
	}
	default:
		break;
	}
}

//ライトの設定関数
void GamePlayScene::settingLight() {
	//標準ライトの設定
	standardLight_.initialize();
	standardLight_.changeLightTypeDir(Vector3(0.0f, -1.0f, 0.0f));
	standardLight_.setLightAmbientColor(Color(0.1f, 0.1f, 0.1f, 0.1f));
	standardLight_.setLghtSpecurColor(Color(0.5f, 0.5f, 0.5f, 0.5f));
	standardLight_.setLightDiffuseColor(Color(0.5f, 0.5f, 0.5f, 0.5f));

	//ライトハンドルの設定
	lightHandle_.setUsePixelLighting(true);
	lightHandle_.createSpotLightHandle("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 500.0f, 0.75f, 0.003f, 0.0f);
	lightHandle_.setLightAmbientColorHandle("Spot", Color(0.0f, 0.0f, 0.0f, 0.0f));
	lightHandle_.setLightDiffuseColorHandle("Spot", Color(0.7f, 0.7f, 0.2f, 1.0f));
	lightHandle_.setLightSpecuarColorHandle("Spot", Color(1.0f, 1.0f, 1.0f, 1.0f));
	//グローバルアンビエントの設定
	standardLight_.setGlobalAmbientLight(Color(0.5f, 0.5f, 0.5f, 0.5f));
}

//UI設定関数
void GamePlayScene::settingUI() {
	//std::shared_ptr<MiniMap> mapUI = std::make_shared<MiniMap>(&world_, Vector2(1020, -100), Vector2(1150, 100));
	//world_.addUI(mapUI);
	std::shared_ptr<WarningManager> warningUI = std::make_shared<WarningManager>(&world_);
	world_.addUI(warningUI);
	std::shared_ptr<TimeUI> timeUI = std::make_shared<TimeUI>(&world_, Vector2(SCREEN_SIZE.x / 2, 50.0f));
	world_.addUI(timeUI);
	std::shared_ptr<StepUI> stepUI = std::make_shared<StepUI>(&world_);
	world_.addUI(stepUI);
	world_.addUI(std::make_shared<Song_Title_UI>(world_.getCanChangedTempoManager().getSoundHandle()));
}