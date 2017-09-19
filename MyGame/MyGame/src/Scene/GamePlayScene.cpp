#include "GamePlayScene.h"
#include"../Graphic/Model.h"
#include"../Camera/Camera.h"
#include"../Actor/ActorGroup.h"
#include"../Actor/Player/Player.h"
#include"../Field/Field.h"
#include"../Actor/Body/BoundingCapsule.h"
#include"../Camera/CameraActor.h"
#include<memory>
#include"../Actor/Enemy/EnemyTemplate.h"

GamePlayScene::GamePlayScene():world_() {

}

void GamePlayScene::start() {
	world_.Initialize();

	std::shared_ptr<Field> field =std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<CameraActor> camera = std::make_shared<CameraActor>(&world_, "Player", Vector3::Zero);
	world_.addCamera(camera);
	std::shared_ptr<BoundingCapsule> caps= std::make_shared<BoundingCapsule>(Vector3(0.0f,0.0f,0.0f), Matrix::Identity, 20.0f, 3.0f);
	std::shared_ptr<Player> player= std::make_shared<Player>(&world_, "Player", Vector3::Up*10.0f, caps);
	world_.addActor(ActorGroup::PLAYER, player);
	world_.addActor(ActorGroup::ENEMY, std::make_shared<EnemyTemplate>(&world_, "Player", Vector3::Up*10.0f));

	world_.getCamera()->setTarget(world_.findActor("Player"));


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
