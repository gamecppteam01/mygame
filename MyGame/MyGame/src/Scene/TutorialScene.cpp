#include "TutorialScene.h"
#include"../Graphic/Model.h"
#include"../Actor/ActorGroup.h"
#include"../Actor/Player/Player.h"
#include"../Field/Field.h"
#include"../Actor/Body/BoundingCapsule.h"
#include"../Camera/OverLookingCamera.h"
#include<memory>
#include"../Actor/Enemy/Enemy_Round/Enemy_Round.h"
#include"../Actor/Enemy/Enemy_Rival/Enemy_Rival.h"
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
#include"../Actor/Other/TutorialPoint.h"
#include"../Actor/Player/TutorialPlayer.h"
#include"../Graphic/EffekseerManager.h"
#include"Screen/TutorialCutIn.h"
#include"Screen/CreateEnemy.h"
#include"../Actor/Player/RegulationMaker.h"
#include"../UI/SpecifiedStepManager.h"
#include"../UI/StepComboManager.h"

std::map<int, SPRITE_ID> cutinList{
	{ 1,SPRITE_ID::CUTIN_LESSON1_SPRITE },
	{ 2,SPRITE_ID::CUTIN_LESSON2_SPRITE },
	{ 3,SPRITE_ID::CUTIN_LESSON3_SPRITE }
};

TutorialScene::TutorialScene()
{
	next_ = SceneType::SCENE_STAGESELECT;
	updateFuncMap_[State::TextDraw] = [&](float deltaTime) {update_textDraw(deltaTime); };
	updateFuncMap_[State::Play] = [&](float deltaTime) {update_Play(deltaTime); };
	updateFuncMap_[State::Pause] = [&](float deltaTime) {update_Pause(deltaTime); };
	updateFuncMap_[State::CutIn] = [&](float deltaTime) {update_CutIn(deltaTime); };
}

TutorialScene::~TutorialScene()
{
	player_.reset();
}

void TutorialScene::start()
{
	Sound::GetInstance().StopBGM();

	light_ = nullptr;

	world_.Initialize();
	settingLight();
	tutorialNumber_ = 1;
	tutorialTiming = 0;
	isEnd_ = false;
	state_ = State::Play;
	prevState_ = State::Play;
	pause_.initialize();
	std::shared_ptr<Field> field = std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<OverLookingCamera> camera = std::make_shared<OverLookingCamera>(&world_, "Camera", Vector3::Zero);
	world_.addCamera(camera);
	int playerNumber = 1;
	player_ = std::make_shared<TutorialPlayer>(&world_, "Player", Vector3::Up*15.0f, this);
	world_.addActor(ActorGroup::PLAYER, player_);
	world_.getCamera()->setTarget(world_.findActor("Player"));
	world_.getCamera()->setFirstPos();

	std::shared_ptr<TutorialPoint> point1 = std::make_shared<TutorialPoint>(Vector3{ -50.0f,3.0f,60.0f });
	world_.addActor(ActorGroup::TUTORIAL, point1);
	std::shared_ptr<TutorialPoint> point2 = std::make_shared<TutorialPoint>(Vector3{ 60.0f,3.0f,60.0f });
	world_.addActor(ActorGroup::TUTORIAL, point2);
	std::shared_ptr<TutorialPoint> point3 = std::make_shared<TutorialPoint>(Vector3{ 0.0f,3.0f,-50.0f });
	world_.addActor(ActorGroup::TUTORIAL, point3);



	world_.getCanChangedTempoManager().setMusic(BGM_ID::STAGE1_BGM, 156.0f);

	std::queue<State>().swap(cutInNextState_);
	std::queue<State>().swap(textNextState_);
	std::stack<SPRITE_ID>().swap(cutInID_);

	cutInID_.push(SPRITE_ID::CUTIN_LESSON1_SPRITE);
	cutInID_.push(SPRITE_ID::CUTIN_INTRODUCT_SPRITE);

	//textNextState_.push(CutIn);//�o�g���_���X�Ƃ́H
	//cutInNextState_.push(TextDraw);//�o�g���_���X�ɂ���
	//textNextState_.push(TextDraw);//�ړ��ɂ���
	//textNextState_.push(Play);//�ړ�������
	changeState(State::TextDraw);

	world_.FindInitialize();

	text_.Reset();

	std::shared_ptr<WarningManager> warningUI = std::make_shared<WarningManager>(&world_);
	world_.addUI(warningUI);

	world_.init_update();

	world_.getCanChangedTempoManager().startMusic();
}

void TutorialScene::update(float deltaTime)
{
	updateFuncMap_[state_](deltaTime);

	if (world_.getCanChangedTempoManager().isEnd()) {
		world_.getCanChangedTempoManager().startMusic();
	}
}

void TutorialScene::draw() const
{
	world_.draw();
	text_.Draw({ 190,0 });
	if (state_ == Pause)pause_.draw();

	if (state_ == CutIn)TutorialCutIn::draw(currentCutIn_, WINDOW_HEIGHT*0.5f, cutInTimer_, StopTime, InTime, OutTime);

	Time::GetInstance().draw_fps();
}

void TutorialScene::end()
{
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE();
	world_.end();
	EffekseerManager::GetInstance().Stop();
	text_.End();
	player_ = nullptr;
	//���C�g�n���h���̑S�폜
	lightHandle_.deleteLightHandleAll();
}

void TutorialScene::changeState(State state) {

	//if (state_ == state)return;//���ɂ��̏�ԂȂ�J�ڂ��Ȃ�

	//��Ԃ̏I���������s��
	switch (state_)
	{
	case TextDraw:
		//world_.getCanChangedTempoManager().restartMusic();//�����Đ�
		player_->textEnd(tutorialNumber_);
		break;
	case Play:
		break;
	case Pause:
		world_.restart();
		break;
	default:
		break;
	}

	//��Ԃ�ς���
	prevState_ = state_;
	state_ = state;

	//�Ή������ύX���������s��
	switch (state_)
	{
	case Reload: {
		end();
		start();
		break;
	}
	case Next: {
		nextTutorial();
		break;
	}
	case CutIn: {
		if (!cutInID_.empty()) {
			currentCutIn_ = cutInID_.top();
			cutInID_.pop();
		}
		cutInTimer_ = 0.0f;
		break;
	}
	case TextDraw:
		text_.Init("Lesson" + std::to_string(tutorialNumber_) + ".txt", 22);

		//world_.getCanChangedTempoManager().pauseMusic();//���𒆒f
		break;
	case Play:
		//CreateEnemy::create(&world_, "res/File/map.csv", 2);
		break;
	case Pause:
		world_.pause();
		pause_.start();
		break;
	default:
		break;
	}
}

void TutorialScene::update_textDraw(float deltaTime)
{
	world_.update_end(deltaTime);
	text_.Update();
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		text_.Check();
	}
	if (text_.isEnd()) {
		//State next = Play;
		//if (!textNextState_.empty()) {
		//	next = textNextState_.front();
		//	textNextState_.pop();
		//}
		changeState(Next);
		return;
	}

}

void TutorialScene::update_Play(float deltaTime)
{
	world_.update(deltaTime);

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		changeState(Pause);
		return;
	}
}

void TutorialScene::update_Pause(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		changeState(State::Play);
		return;
	}
	world_.update_end(deltaTime);

	GamePlayState state;
	int p = pause_.update(deltaTime, next_, state);
	if (p == 1) {
		isEnd_ = true;
	}
	else if (p == 2) {
		if (state == GamePlayState::Reload)changeState(Reload);
		else changeState(Play);
	}

}

void TutorialScene::update_CutIn(float deltaTime)
{
	world_.update_end(deltaTime);
	cutInTimer_ += deltaTime;
	if (cutInTimer_ >= StopTime + InTime + OutTime) {
		//State next = TextDraw;
		//if (!cutInNextState_.empty()) {
		//	next = cutInNextState_.front();
		//	cutInNextState_.pop();
		//}
		changeState(Next);
	}
}

int TutorialScene::getTutorialNum() const
{
	return tutorialNumber_;
}

void TutorialScene::nextTutorial()
{
	tutorialTiming++;

	switch (tutorialNumber_)
	{
	case 1: {//�悤����
		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_INTRODUCT_SPRITE);
			changeState(CutIn);//�o�g���_���X�Ƃ�
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����
			return;
			break;
		}
		default:
			break;
		}
		break;
	}
	case 2: {//�o�g���_���X�Ƃ�

		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_LESSON1_SPRITE);
			changeState(CutIn);//�ړ�
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 3: {

		switch (tutorialTiming)
		{
		case 1: {
			changeState(Play);//�ړ�
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			cutInID_.push(SPRITE_ID::CUTIN_LESSON2_SPRITE);
			changeState(CutIn);//�X�e�b�v
			break;
		}
		case 4: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 4: {
		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_QUARTER_SPRITE);
			changeState(CutIn);//�N�H�[�^�[
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 5: {
		switch (tutorialTiming)
		{
		case 1: {
			changeState(Play);//�N�H�[�^�[
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 6: {
		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_TURN_SPRITE);
			changeState(CutIn);//�^�[��
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 7: {
		switch (tutorialTiming)
		{
		case 1: {
			changeState(Play);//�^�[��
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 8: {
		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_HALF_SPRITE);
			changeState(CutIn);//�n�[�t
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 9: {
		switch (tutorialTiming)
		{
		case 1: {
			changeState(Play);//�n�[�t
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 10: {
		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_SPIN_SPRITE);
			changeState(CutIn);//�X�s��
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 11: {
		switch (tutorialTiming)
		{
		case 1: {
			changeState(Play);//�X�s��
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 12: {
		switch (tutorialTiming)
		{
		case 1: {
			cutInID_.push(SPRITE_ID::CUTIN_LESSON3_SPRITE);
			changeState(CutIn);//�X�|�b�g���C�g
			break;
		}
		case 2: {
			nextTutorialCount();
			changeState(TextDraw);//����

			break;
		}
		default:
			break;
		}
		break;
	}
	case 13: {
		switch (tutorialTiming)
		{
		case 1: {
			light_ = std::make_shared<Judgement_SpotLight>(&world_, Vector3(0.0f, 2.0f, 0.0f), lightHandle_);
			world_.addActor(ActorGroup::NPC, light_);

			changeState(Play);//�X�|�b�g���C�g
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			if (light_.use_count()>0)light_->dead();

			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 14: {
		switch (tutorialTiming)
		{
		case 1: {
			auto specStepMgr = std::make_shared<SpecifiedStepManager>(&world_);
			world_.addUI(specStepMgr);
			RegulationMaker::SetRegulationTutorial(player_, specStepMgr);//�K��̐ݒ�
			
			changeState(Play);//�K��
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 15: {
		switch (tutorialTiming)
		{
		case 1: {
			auto stepcomboManager = std::make_shared<StepComboManager>(&world_);
			world_.addUI(stepcomboManager);

			player_->resetCombo();
			changeState(Play);//�|�C���g�A�b�v�R���{
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 16: {
		switch (tutorialTiming)
		{
		case 1: {
			player_->resetCombo();
			changeState(Play);//�o�[�X�g�R���{
			break;
		}
		case 2: {
			cutInID_.push(SPRITE_ID::CUTIN_SUCCESS_SPRITE);
			changeState(CutIn);//����
			break;
		}
		case 3: {
			nextTutorialCount();
			changeState(TextDraw);//����
			break;
		}
		default:
			break;
		}
		break;
	}
	case 17: {
		isEnd_ = true;
		next_ = SceneType::SCENE_TITLE;
		return;
	}
	default:
		break;
	}
}

void TutorialScene::nextLesson()
{
	if (state_ == Play) {
		changeState(Next);
	}
}

void TutorialScene::settingLight()
{
	//�W�����C�g�̐ݒ�
	standardLight_.initialize();
	standardLight_.changeLightTypeDir(Vector3(0.0f, -1.0f, 0.0f));
	standardLight_.setLightAmbientColor(Color(0.1f, 0.1f, 0.1f, 0.1f));
	standardLight_.setLghtSpecurColor(Color(0.5f, 0.5f, 0.5f, 0.5f));
	standardLight_.setLightDiffuseColor(Color(0.5f, 0.5f, 0.5f, 0.5f));

	//���C�g�n���h���̐ݒ�
	lightHandle_.setUsePixelLighting(true);
	lightHandle_.createSpotLightHandle("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 500.0f, 0.75f, 0.003f, 0.0f);
	lightHandle_.setLightAmbientColorHandle("Spot", Color(0.0f, 0.0f, 0.0f, 0.0f));
	lightHandle_.setLightDiffuseColorHandle("Spot", Color(0.7f, 0.7f, 0.2f, 1.0f));
	lightHandle_.setLightSpecuarColorHandle("Spot", Color(1.0f, 1.0f, 1.0f, 1.0f));
	//�O���[�o���A���r�G���g�̐ݒ�
	standardLight_.setGlobalAmbientLight(Color(0.5f, 0.5f, 0.5f, 0.5f));
	lightHandle_.setLightEnableHandle("Spot", false);

}

void TutorialScene::nextTutorialCount()
{
	tutorialTiming = 0;
	tutorialNumber_++;

}
