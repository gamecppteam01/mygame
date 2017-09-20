#include "World.h"
#include"../Field/Field.h"
#include"../Camera/CameraActor.h"
#include"../Light/LightActor.h"

// コンストラクタ
World::World() :
	listener_([](EventMessage, void*) {}),
	field_(std::make_shared<Field>()),
	camera_(std::make_shared<CameraActor>()){
}

//初期化
void World::Initialize()
{
	//各値を初期値に
	field_ = std::make_shared<Field>();
	camera_ = std::make_shared<CameraActor>();
//	light_ = std::make_shared<LightActor>();
	actors_.initialize();
	listener_ = [](EventMessage, void*) {};
}

// 更新
void World::update(float deltaTime) {
	field_->update(deltaTime);
	// アクターの更新処理
	actors_.update(deltaTime);
	camera_->update(deltaTime);
	light_->update(deltaTime);
}

// 描画
void World::draw() const {
	field_->draw();
	camera_->draw();
	light_->draw();
	// アクターの描画処理
	actors_.draw();
}

// メッセージ処理
void World::handleMessage(EventMessage message, void* param) {
	// アクターのメッセージ処理
	actors_.handleMessage(message, param);
}

void World::addField(const FieldPtr & field)
{
	field_ = field;
}

void World::addCamera(const CameraPtr & camera)
{
	camera_ = camera;
}

void World::addLight(const LightPtr & light)
{
	light_ = light;
}

FieldPtr World::getField() const
{
	return field_;
}

CameraPtr World::getCamera()
{
	return camera_;
}


// アクターの追加
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// アクターの検索
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}


// メッセージの送信
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// イベントリスナーの追加
void World::addEventMessageListener(std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

void World::end()
{
	field_ = nullptr;
	actors_.initialize();
	listener_ = nullptr;
}


