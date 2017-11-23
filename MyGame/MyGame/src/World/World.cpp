#include "World.h"
#include"../Field/Field.h"
#include"../Camera/OverLookingCamera.h"
#include"../Graphic/EffekseerManager.h"

// �R���X�g���N�^
World::World() :
	listener_([](EventMessage, void*) {}),
	field_(std::make_shared<Field>()),
	camera_(std::make_shared<OverLookingCamera>()),
	light_(true),
	uiManager_(),
	stepTimer_(),
	scoreManager_(this),
	scoreMap_(this),
	tempo_(),
	shadowmap_() {
}

World::~World()
{
	lateDrawFuncList_.clear();
	lateDrawFuncListAfterUI_.clear();
	end();
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
	tempo_.initialize();
	//scoreManager_.initialize();
	listener_ = [](EventMessage, void*) {};

	lateDrawFuncList_.clear();
	lateDrawFuncListAfterUI_.clear();

	//if (ShadowMapHandle != -1) return;
	//�V���h�E�}�b�v�̐ݒ�
	shadowflag_ = false;
	shadowmap_.Clear();
	shadowmap_.Set(SHADOW_MAP_ID::SHADOW_MAP_01, shadowmap_.RESOLUTION_4096, -Vector3::Up);
	shadowmap_.SetRange(Vector3(-1000.0f, -1.0f, -1000.0f), Vector3(1000.0f, 1000.0f, 1000.0f));
}
void World::FindInitialize() {
	scoreManager_.initialize();
	scoreMap_.initialize();
}

// �X�V
void World::update(float deltaTime) {
	camera_->update(deltaTime);
	uiManager_.update(deltaTime);
	field_->update(deltaTime);
	scoreMap_.update(deltaTime);
	tempo_.update(deltaTime);

	if (IsPause_ == false) return;

	stepTimer_.update(deltaTime);
	scoreManager_.updata(deltaTime);

	// �A�N�^�[�̍X�V����
	actors_.update(deltaTime);
	lateDrawFuncList_.clear();//�`��֐��̃��Z�b�g
}

// �`��
void World::draw() const {
	switch (shadowflag_)
	{
	case true:
		shadowdraw();
		break;
	case false:
		normaldraw();
		break;
	}

	EffekseerManager::GetInstance().Draw();

	//�A�N�^�[�n�̒x���`��
	for (auto& d : lateDrawFuncList_) {
		d();
	}
	uiManager_.draw();
	for (auto& d : lateDrawFuncListAfterUI_) {
		d();
	}

	tempo_.draw();

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
	light_.SetAmbientColor(light.handlename, light.color.ambient);
	light_.SetDiffuseColor(light.handlename, light.color.diffuse);
	light_.SetAmbientColor(light.handlename, light.color.ambient);
}

void World::addLight(SpotLight light)
{
	light_.SetSpotLight(light.handlename, light.position, light.vector, light.cone_outangle, light.cone_inangle, light.range);
}

void World::addLight(PointLight light)
{
	light_.SetPointLight(light.handlename, light.position, light.range);
}

void World::addUI(UIPtr ui)
{
	uiManager_.add(ui);
}
UIPtr World::findUI(const std::string & name)
{
	return uiManager_.find(name);
}

void World::addStepTimeListener(const ActorPtr & actor)
{
	tempo_.setActor(actor);
}

FieldPtr World::getField() const
{
	return field_;
}

CameraPtr World::getCamera()
{
	return camera_;
}

ScoreManager World::getScoreManager() const { return scoreManager_; }

ScoreManager & World::getCanChangedScoreManager() {
	return scoreManager_;
}

ScoreMap & World::getCanChangedScoreMap()
{
	return scoreMap_;
}

TempoManager & World::getCanChangedTempoManager()
{
	return tempo_;
}
TempoManager World::getTempoManager()const
{
	return tempo_;
}

// �A�N�^�[�̒ǉ�
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// �A�N�^�[�̌���
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}

void World::findActors(const std::string & name, std::list<ActorPtr>& actorList) {
	actors_.findActor(name, actorList);
}
void World::findActors(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList) {
	actors_.findActor(name, actorList);
}


// ���b�Z�[�W�̑��M
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

void World::worldStop()
{
	IsPause_ = false;
}

void World::worldStart()
{
	IsPause_ = true;
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
	shadowmap_.Clear();
}

void World::setLateDraw(std::function<void()> draw, bool isBeforeUI)
{
	if (isBeforeUI)lateDrawFuncList_.emplace_back(draw);
	else lateDrawFuncListAfterUI_.emplace_back(draw);
}

void World::setShadowMap(const bool flag) {
	shadowflag_ = flag;
}

void World::normaldraw() const {
	camera_->draw();
	field_->draw();
	// �A�N�^�[�̕`�揈��
	actors_.draw();
}

void World::shadowdraw() const {
	//�V���h�E�}�b�v�ɕ`��
	shadowmap_.Begin(SHADOW_MAP_ID::SHADOW_MAP_01);
	// �A�N�^�[�̕`�揈��
	actors_.draw();
	shadowmap_.End();

	//�g�p�������V���h�E�}�b�v��ݒ肵�ĕ`��
	shadowmap_.Enable(SHADOW_MAP_ID::SHADOW_MAP_01, 0);
	camera_->draw();
	field_->draw();
	// �A�N�^�[�̕`�揈��
	actors_.draw();
	shadowmap_.Disable(0);
}
