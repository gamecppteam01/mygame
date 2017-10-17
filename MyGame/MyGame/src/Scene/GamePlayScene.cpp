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
#include"../UI/UITemplate.h"
#include<EffekseerForDXLib.h>
#include"../Actor/Judge_NPC/Judge_NPC.h"

GamePlayScene::GamePlayScene():world_() {
}

void GamePlayScene::start() {
	world_.Initialize();

	std::shared_ptr<Field> field =std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<OverLookingCamera> camera = std::make_shared<OverLookingCamera>(&world_, "Camera", Vector3::Zero);
	world_.addCamera(camera);
	std::shared_ptr<Player> player= std::make_shared<Player>(&world_, "Player", Vector3::Up*10.0f);
	world_.addActor(ActorGroup::PLAYER, player);
	//for (int i = 0; i < 4; i++) {
	//	world_.addActor(ActorGroup::ENEMY, std::make_shared<BaseEnemy>(&world_, "Enemy", Vector3::Up*10.0f+Vector3(10.0f*i)));
	//}
	world_.addActor(ActorGroup::NPC, std::make_shared<Judge_NPC>(&world_, "Judge", Vector3(10.0f, 10.0f, 20.0f)));
	world_.getCamera()->setTarget(world_.findActor("Player"));

	//std::shared_ptr<UITemplate> uiptr = std::make_shared<UITemplate>(Vector2(200, 200));
	//world_.addUI(uiptr);
}

void GamePlayScene::update(float deltaTime) {

	world_.update(deltaTime);

}

void GamePlayScene::draw() const {
	//Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, Matrix::Identity);

	world_.draw();
}

void GamePlayScene::end() {
	world_.Initialize();
}
