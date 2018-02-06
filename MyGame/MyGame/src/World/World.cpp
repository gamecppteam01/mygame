#include "World.h"
#include"../Field/Field.h"
#include"../Camera/OverLookingCamera.h"
#include"../Graphic/EffekseerManager.h"
#include"../DataManager/DataManager.h"

// �R���X�g���N�^
World::World() :
	listener_([](EventMessage, void*) {}),
	field_(std::make_shared<Field>()),
	camera_(std::make_shared<OverLookingCamera>()),
	roundCamera_(this),
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
	//end();
}

//������
void World::Initialize()
{
	//�e�l�������l��
	field_ = std::make_shared<Field>();
	camera_ = std::make_shared<OverLookingCamera>();
	roundCamera_ = RoundCamera(this);
	light_.Initialize();
	actors_.initialize();
	uiManager_.initialize();
	stepTimer_.initialize();
	tempo_.initialize();
	//scoreManager_.initialize();
	listener_ = [](EventMessage, void*) {};

	lateDrawFuncList_.clear();
	lateDrawFuncListAfterUI_.clear();

	//�V���h�E�}�b�v�̐ݒ�
	shadowflag_ = false;
	shadowmap_.initialize();
}
void World::FindInitialize() {
	scoreManager_.initialize();
	scoreMap_.initialize();
}

void World::pause()
{
	actors_.pause();
	tempo_.pauseMusic();
	uiManager_.pause();
}

void World::restart()
{
	actors_.restart();
	tempo_.restartMusic();
	uiManager_.restart();
}

// �X�V
void World::update(float deltaTime) {
	scoreMap_.update(deltaTime);
	stepTimer_.update(deltaTime);
	field_->update(deltaTime);
	scoreManager_.updata(deltaTime);
	// �A�N�^�[�̍X�V����
	actors_.update(deltaTime);
	if(roundCamera_.isEnd())camera_->update(deltaTime);
	else roundCamera_.onUpdate(deltaTime);
	uiManager_.update(deltaTime);
	tempo_.update(deltaTime);

	lateDrawFuncList_.clear();//�`��֐��̃��Z�b�g
	lateDrawFuncListAfterUI_.clear();

	EffekseerManager::GetInstance().Update();
}

void World::update_end(float deltaTime)
{
	if (!roundCamera_.isEnd())roundCamera_.onUpdate(deltaTime);
	uiManager_.update(deltaTime);
	lateDrawFuncList_.clear();
	lateDrawFuncListAfterUI_.clear();
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
	roundCamera_.onDraw();
	tempo_.draw();

}

// ���b�Z�[�W����
void World::handleMessage(EventMessage message, void* param) {
	// �A�N�^�[�̃��b�Z�[�W����
	actors_.handleMessage(message, param);
}

void World::init_update(){
	// �A�N�^�[�̍X�V����
	actors_.update(1.0f/60.0f);
	camera_->update(1.0f / 60.0f);
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

// �C�x���g���X�i�[�̒ǉ�
void World::addEventMessageListener(std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

void World::end()
{
	field_ = nullptr;
	actors_.initialize();
	listener_ = nullptr;
	shadowmap_.AllDeletionShadowMap();
}

void World::setLateDraw(std::function<void()> draw, bool isBeforeUI)
{
	if (isBeforeUI)lateDrawFuncList_.emplace_back(draw);
	else lateDrawFuncListAfterUI_.emplace_back(draw);
}

void World::setShadowMap(const bool flag, const MODEL_ID& id) {
	shadowflag_ = flag;

	shadow_data = DataManager::GetInstance().getShadowData(id);
	shadowmap_.makeShadowMap(shadow_data.Id, shadow_data.Size, shadow_data.Direction);
	shadowmap_.AllSetRange(shadow_data.MinPos, shadow_data.MaxPos);
}

void World::setFieldAudienceBright(float r, float g, float b)
{
	field_->AudienceLightColor(r, g, b);
}

void World::roundCam(int num)
{
	roundCamera_.init();
	roundCamera_.setStage(num);
}

void World::stopRound()
{
	roundCamera_.endRound();
}

void World::normaldraw() const {
	camera_->draw();
	field_->draw();
	// �A�N�^�[�̕`�揈��
	actors_.draw();
}

void World::shadowdraw() const {
	//�V���h�E�}�b�v�ɕ`��
	shadowmap_.SetUp_ShadowMapDraw(shadow_data.Id);
	// �A�N�^�[�̕`�揈��
	actors_.shadowDraw();
	shadowmap_.DrawEnd_ShadowMap();

	camera_->draw();
	//�g�p�������V���h�E�}�b�v��ݒ肵�ĕ`��
	shadowmap_.SetUse_ShadowMap(shadow_data.Id, shadow_data.Slot);
	field_->draw();
	// �A�N�^�[�̕`�揈��
	actors_.draw();
	shadowmap_.ReleaseShadowMap(shadow_data.Slot);

	//shadowmap_.Draw_Test(SHADOW_MAP_ID::SHADOW_MAP_01, Vector2(0, 0), Vector2(1280, 720));
}
