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

std::map<int,SPRITE_ID> cutinList{
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

	world_.Initialize();
	tutorialNumber_ = 1;
	isEnd_ = false;
	state_ = State::Play;
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
	
	cutInNextState_.push(TextDraw);
	cutInNextState_.push(Play);
	textNextState_.push(CutIn);
	changeState(State::CutIn);

	world_.FindInitialize();

	text_.Reset();
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
}

void TutorialScene::end()
{
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE();
	world_.end();
	EffekseerManager::GetInstance().Stop();
	text_.End();
	player_ = nullptr;
}

void TutorialScene::changeState(State state) {

	if (state_ == state)return;//���ɂ��̏�ԂȂ�J�ڂ��Ȃ�

							   //��Ԃ̏I���������s��
	switch (state_)
	{
	case TextDraw:
		world_.getCanChangedTempoManager().restartMusic();//�����Đ�
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
	state_ = state;

	//�Ή������ύX���������s��
	switch (state_)
	{
	case Reload: {
		end();
		start();
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

		world_.getCanChangedTempoManager().pauseMusic();//�����Đ�
		break;
	case Play:
		CreateEnemy::create(&world_, "res/File/map.csv", 2);
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
	text_.Update();
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		text_.Check();
	}
	if (text_.isEnd()) {
		State next = Play;
		if (!textNextState_.empty()) {
			next = textNextState_.front();
			textNextState_.pop();
		}
		changeState(next);
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
	cutInTimer_ += deltaTime;
	if (cutInTimer_ >= StopTime+ InTime+ OutTime) {
		State next = TextDraw;
		if (!cutInNextState_.empty()) {
			next = cutInNextState_.front();
			cutInNextState_.pop();
		}
		changeState(next);
	}
}

int TutorialScene::getTutorialNum() const
{
	return tutorialNumber_;
}

void TutorialScene::nextLesson()
{
	if (state_ == Play) {
		tutorialNumber_++;
		if (tutorialNumber_ > 3) {
			isEnd_ = true;
			next_ = SceneType::SCENE_TITLE;
			return;
		}

		cutInID_.push(cutinList[tutorialNumber_]);
		changeState(CutIn);
	}
}
