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

//ゲームの時間
static const float gameTime = 5.0f;

GamePlayScene::GamePlayScene():world_(), scoreDisplay_(nullptr),playerEffectDraw_(nullptr),standardLight_(),lightHandle_(){
	//更新遷移先の設定
	updateFuncMap_[GamePlayState::Start] = [&](float deltaTime) {update_Start(deltaTime); };
	updateFuncMap_[GamePlayState::Play] = [&](float deltaTime) {update_Play(deltaTime); };
	updateFuncMap_[GamePlayState::Pause] = [&](float deltaTime) {update_Pause(deltaTime); };
	updateFuncMap_[GamePlayState::End] = [&](float deltaTime) {update_End(deltaTime); };

}

void GamePlayScene::start() {
	world_.Initialize();
	world_.setShadowMap(true);
	FadePanel::GetInstance().SetInTime(1.0f);
	FadePanel::GetInstance().FadeIn();
	FadePanel::GetInstance().AddCollBack([&] {FadePanel::GetInstance().IsClearScreen() == true; });

	state_ = GamePlayState::Start;

	std::shared_ptr<Field> field =std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<OverLookingCamera> camera = std::make_shared<OverLookingCamera>(&world_, "Camera", Vector3::Zero);
	world_.addCamera(camera);

	//選手番号
	int playerNumber = 1;
	std::shared_ptr<Player> player= std::make_shared<Player>(&world_, "Player", Vector3::Up*15.0f, playerNumber);
	world_.addActor(ActorGroup::PLAYER, player);
	for (int i = 0; i < 0; i++) {
		playerNumber++;
		auto enemy = std::make_shared<Enemy_Quick>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(40.0f*i,0.f,30.f), playerNumber);
		world_.addActor(ActorGroup::ENEMY, enemy);
		world_.addStepTimeListener(enemy);
	}
	playerNumber++;
	auto enemy = std::make_shared<NormalEnemy>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(-30.f, 0.f, 30.f), playerNumber);
	world_.addActor(ActorGroup::ENEMY, enemy);
	//playerNumber++;
	//auto enemy2 = std::make_shared<Enemy_Power>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(70.f, 0.f, -60.f), playerNumber);
	//world_.addActor(ActorGroup::ENEMY, enemy2);
	//playerNumber++;
	//auto enemy3 = std::make_shared<Enemy_Round>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(40.f, 0.f, -20.f), playerNumber);
	//world_.addActor(ActorGroup::ENEMY, enemy3);
	world_.addStepTimeListener(enemy);
	//world_.addStepTimeListener(enemy2);
	//world_.addStepTimeListener(enemy3);

	world_.addStepTimeListener(player);

	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(-110.0f, 10.0f, 60.0f),Matrix::CreateRotationY(-45.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(110.0f, 10.0f, 60.0f), Matrix::CreateRotationY(45.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(110.0f, 10.0f, -60.0f), Matrix::CreateRotationY(135.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, Vector3(-110.0f, 10.0f, -60.0f), Matrix::CreateRotationY(-135.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judgement_SpotLight>(&world_, Vector3(0.0f, 2.0f, 0.0f)));
	world_.getCamera()->setTarget(world_.findActor("Player"));
	world_.getCamera()->setFirstPos();

	std::shared_ptr<MiniMap> mapUI = std::make_shared<MiniMap>(&world_, Vector2(1020, -100),Vector2(1150,100));
	world_.addUI(mapUI);
	std::shared_ptr<WarningManager> warningUI = std::make_shared<WarningManager>(&world_);
	world_.addUI(warningUI);
	std::shared_ptr<EndUI> endUI = std::make_shared<EndUI>(&world_.getCanChangedTempoManager(), Vector2(500, 500));
	world_.addUI(endUI);
	std::shared_ptr<TimeUI> timeUI = std::make_shared<TimeUI>(&world_, Vector2(SCREEN_SIZE.x / 2 - 50.0f, 0.0f));
	world_.addUI(timeUI);
	//std::shared_ptr<UITemplate> uiptr = std::make_shared<UITemplate>(Vector2(200, 200));
	//world_.addUI(uiptr);

	scoreDisplay_.initialize();
	scoreDisplay_.setScoreManager(&world_.getCanChangedScoreManager());

	//アクター検索を掛けるクラス群の初期化
	world_.FindInitialize();

	//音リソのセット
	world_.getCanChangedTempoManager().setMusic("res/Sound/bgm/stage1a_bgm.wav", 156.0f);

	//標準ライトの設定
	standardLight_.initialize();
	standardLight_.changeLightTypeDir(Vector3(1.0f, -1.0f, 0.0f));
	standardLight_.setLightEnable(false);
	//ライトハンドルの設定
	lightHandle_.setUsePixelLighting(true);
	lightHandle_.createSpotLightHandle("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), out_angle, in_angle, range, atten0, atten1, atten2);
	lightHandle_.setLightAmbientColorHandle("Spot", Color(0.0f, 0.0f, 0.0f, 0.0f));
	lightHandle_.setLightDiffuseColorHandle("Spot", Color(1.0f, 1.0f, 1.0f, 1.0f));
	lightHandle_.setLightSpecuarColorHandle("Spot", Color(1.0f, 1.0f, 1.0f, 1.0f));
	//グローバルアンビエントの設定
	standardLight_.setGlobalAmbientLight(Color(0, 0, 0, 0));

	playerEffectDraw_.Initialize();
	playerEffectDraw_.setPlayerEffectDraw(player.get());

	//changeState(GamePlayState::Play);
}

void GamePlayScene::update(float deltaTime) {
	updateFuncMap_[state_](deltaTime);//更新


}

void GamePlayScene::draw() const {
	
	world_.draw();
	
	for (int i = 1; i < world_.getScoreManager().GetCharacterCount()+1; i++) {
		DebugDraw::DebugDrawFormatString(200, 500 + i * 30, GetColor(255, 255, 255), "%iscore:%i", i, world_.getScoreManager().GetCharacterScore(i));
	}
	
	//NumberManager::GetInstance().DrawNumber(Vector2(WINDOW_WIDTH / 2, 0.f), (int)world_.getTempoManager().getRemainTime());
	
	//ライトテスト変数デバック描画
	DebugDraw::DebugDrawFormatString(300, 500, GetColor(255, 0, 255), "out_angle:%f", out_angle);
	DebugDraw::DebugDrawFormatString(300, 530, GetColor(255, 0, 255), "in_angle:%f", in_angle);
	DebugDraw::DebugDrawFormatString(300, 560, GetColor(255, 0, 255), "atten0:%f", atten0);
	DebugDraw::DebugDrawFormatString(300, 590, GetColor(255, 0, 255), "atten1:%f", atten1);
	DebugDraw::DebugDrawFormatString(300, 620, GetColor(255, 0, 255), "atten2:%f", atten2);
	DebugDraw::DebugDrawFormatString(300, 650, GetColor(255, 0, 255), "range:%f", range);

	Time::GetInstance().draw_fps();
	scoreDisplay_.Score(Vector2(0,25),5);

	if(state_!=GamePlayState::Start)playerEffectDraw_.Draw();

}

void GamePlayScene::end() {
	world_.Initialize();
	std::list<ScoreData> list;
	world_.getScoreManager().getScoreDataList(list);
	DataManager::GetInstance().setData(list);

	scoreDisplay_.finalize();
	lightHandle_.deleteLightHandleAll();
	playerEffectDraw_.finalize();

	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE();
}

void GamePlayScene::update_Start(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		changeState(GamePlayState::Play);
		return;
	}
	world_.update_end(deltaTime);
}

void GamePlayScene::update_Play(float deltaTime)
{
	world_.update(deltaTime);

	if (world_.getCanChangedTempoManager().isEnd()) {
		changeState(GamePlayState::End);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		changeState(GamePlayState::Pause);
		return;
	}

	//スポットライトの値操作(値が定まったら消します)
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S)) {
		out_angle += 0.1f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::X)) {
		out_angle -= 0.1f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::D)) {
		in_angle += 0.1f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::C)) {
		in_angle -= 0.1f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::F)) {
		atten0 += 0.001f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::V)) {
		atten0 -= 0.001f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::G)) {
		atten1 += 0.001f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B)) {
		atten1 -= 0.001f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y)) {
		atten2 += 0.001f;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::N)) {
		atten2 -= 0.001f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::J)) {
		range += 1.0f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::M)) {
		range -= 1.0f;
	}
	lightHandle_.setLightAngleHandle("Spot", out_angle, in_angle);
	lightHandle_.setLightRangeAttenHandle("Spot", range, atten0, atten1, atten2);

	//playerEffectDraw_.Update(deltaTime);

}

void GamePlayScene::update_Pause(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		changeState(GamePlayState::Play);
		return;
	}
	world_.update_end(deltaTime);
}

void GamePlayScene::update_End(float deltaTime)
{
	UIPtr p = world_.findUI("EndUI");
	std::shared_ptr<EndUI> endUi = std::static_pointer_cast<EndUI>(p);
	if (endUi->end()) {
		isEnd_ = true;
		next_ = SceneType::SCENE_CLEAR;
	}
	world_.update_end(deltaTime);

}

void GamePlayScene::changeState(GamePlayState state)
{
	if (state_ == state)return;//既にその状態なら遷移しない

	//状態の終了処理を行う
	switch (state_)
	{
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
	case Start:
		break;
	case Play:
		break;
	case Pause:
		playerEffectDraw_.pauseSound();

		world_.pause();
		break;
	case End:
		break;
	default:
		break;
	}
}
