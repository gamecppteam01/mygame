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
#include"../Actor/Enemy/Enemy_Quick/Enemy_Quick.h"

#include"../UI/UITemplate.h"
#include<EffekseerForDXLib.h>
#include"../Actor/Judge/Judge_NPC/Judge_NPC.h"
#include"../Actor/Judge/Judgement_SpotLight/Judgement_SpotLight.h"
#include"../UI/UIInclude.h"
#include"../Input/InputChecker.h"
#include"../Game/Time.h"
#include"../DataManager/DataManager.h"

GamePlayScene::GamePlayScene():world_(), scoreDisplay_(nullptr){
}

void GamePlayScene::start() {
	world_.Initialize();

	std::shared_ptr<Field> field =std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<OverLookingCamera> camera = std::make_shared<OverLookingCamera>(&world_, "Camera", Vector3::Zero);
	world_.addCamera(camera);

	//選手番号
	int playerNumber = 1;
	std::shared_ptr<Player> player= std::make_shared<Player>(&world_, "Player", Vector3::Up*15.0f, playerNumber);
	world_.addActor(ActorGroup::PLAYER, player);
	for (int i = 0; i < 1; i++) {
		playerNumber++;
		auto enemy = std::make_shared<Enemy_Quick>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(40.0f*i,0.f,30.f), playerNumber);
		world_.addActor(ActorGroup::ENEMY, enemy);
		world_.addStepTimeListener(enemy);
	}
	playerNumber++;
	auto enemy = std::make_shared<NormalEnemy>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(-30.f, 0.f, 30.f), playerNumber);
	world_.addActor(ActorGroup::ENEMY, enemy);
	playerNumber++;
	auto enemy2 = std::make_shared<Enemy_Power>(&world_, "Enemy", Vector3::Up*15.0f + Vector3(70.f, 0.f, -60.f), playerNumber);
	world_.addActor(ActorGroup::ENEMY, enemy2);
	world_.addStepTimeListener(enemy);
	world_.addStepTimeListener(enemy2);

	world_.addStepTimeListener(player);

	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(70.0f, 10.0f, 20.0f),Matrix::CreateRotationY(30.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(-80.0f, 10.0f, -20.0f), Matrix::CreateRotationY(130.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(-30.0f, 10.0f, 95.0f), Matrix::CreateRotationY(-60.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(100.0f, 10.0f, -60.0f), Matrix::CreateRotationY(-150.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(40.0f, 10.0f, -40.0f), Matrix::CreateRotationY(-150.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(-20.0f, 10.0f, 30.0f), Matrix::CreateRotationY(-150.0f)));
	world_.addActor(ActorGroup::NPC, std::make_shared<Judgement_SpotLight>(&world_, "Judge", Vector3(0.0f, 10.0f, 0.0f)));
	world_.getCamera()->setTarget(world_.findActor("Player"));

	std::shared_ptr<MiniMap> mapUI = std::make_shared<MiniMap>(&world_, Vector2(1000, 0),player->position());
	world_.addUI(mapUI);
	std::shared_ptr<WarningManager> warningUI = std::make_shared<WarningManager>(&world_);
	world_.addUI(warningUI);
	//std::shared_ptr<UITemplate> uiptr = std::make_shared<UITemplate>(Vector2(200, 200));
	//world_.addUI(uiptr);

	scoreDisplay_.initialize();
	scoreDisplay_.setScoreManager(&world_.getCanChangedScoreManager());

	//アクター検索を掛けるクラス群の初期化
	world_.FindInitialize();
}

void GamePlayScene::update(float deltaTime) {
	world_.update(deltaTime);
}

void GamePlayScene::draw() const {
	world_.draw();

	for (int i = 1; i < world_.getScoreManager().GetCharacterCount()+1; i++) {
		DebugDraw::DebugDrawFormatString(200, 500 + i * 30, GetColor(255, 255, 255), "%iscore:%i", i, world_.getScoreManager().GetCharacterScore(i));
	}
	
	Time::GetInstance().draw_fps();

	scoreDisplay_.Score();
}

void GamePlayScene::end() {
	world_.Initialize();
	std::list<ScoreData> list;
	world_.getScoreManager().getScoreDataList(list);
	DataManager::GetInstance().setData(list);

	scoreDisplay_.finalize();
}
