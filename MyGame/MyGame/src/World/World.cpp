#include "World.h"
#include"../Field/Field.h"
#include"../Camera/OverLookingCamera.h"

// �R���X�g���N�^
World::World() :
	listener_([](EventMessage, void*) {}),
	field_(std::make_shared<Field>()),
	camera_(std::make_shared<OverLookingCamera>()),
	light_(true),
	uiManager_(),
	stepTimer_(){
}

//������
void World::Initialize()
{
	//�e�l�������l��
	field_ = std::make_shared<Field>();
	camera_ = std::make_shared<OverLookingCamera>();
	light_.Initialize();
	actors_.initialize();
	uiManager_.initialize();
	stepTimer_.initialize();
	listener_ = [](EventMessage, void*) {};
}

// �X�V
void World::update(float deltaTime) {
	stepTimer_.update(deltaTime);
	field_->update(deltaTime);
	// �A�N�^�[�̍X�V����
	actors_.update(deltaTime);
	camera_->update(deltaTime);
	uiManager_.update(deltaTime);
}

// �`��
void World::draw() const {
	field_->draw();
	camera_->draw();
	// �A�N�^�[�̕`�揈��
	actors_.draw();
	uiManager_.draw();
}

// ���b�Z�[�W����
void World::handleMessage(EventMessage message, void* param) {
	// �A�N�^�[�̃��b�Z�[�W����
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

void World::addLight(DirectionalLight light)
{
	light_.SetDirectionalLight(light.handlename, light.vector);
}

void World::addLight(SpotLight light)
{
	light_.SetSpotLight(light.handlename,light.position, light.vector, light.cone_outangle, light.cone_inangle, light.range);
}

void World::addLight(PointLight light)
{
	light_.SetPointLight(light.handlename, light.position, light.range);
}

void World::addUI(UIPtr ui)
{
	uiManager_.add(ui);
}

void World::addStepTimeListener(const ActorPtr & actor)
{
	stepTimer_.addActor(actor);
}

FieldPtr World::getField() const
{
	return field_;
}

CameraPtr World::getCamera()
{
	return camera_;
}

StepTimer World::getStepTimer() const
{
	return stepTimer_;
}

// �A�N�^�[�̒ǉ�
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// �A�N�^�[�̌���
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}

void World::findActors(const std::string & name, std::list<ActorPtr>& actorList){
	actors_.findActor(name, actorList);
}


// ���b�Z�[�W�̑��M
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// �C�x���g���X�i�[�̒ǉ�
void World::addEventMessageListener(std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

void World::end()
{
	field_ = nullptr;
	actors_.initialize();
	listener_ = nullptr;
}
