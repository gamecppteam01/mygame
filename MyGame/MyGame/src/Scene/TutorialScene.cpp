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

TutorialScene::TutorialScene()
{
	next_ = SceneType::SCENE_STAGESELECT;
	updateFuncMap_[State::TextDraw] = [&](float deltaTime) {update_textDraw(deltaTime); };
	updateFuncMap_[State::Play] = [&](float deltaTime) {update_Play(deltaTime); };
	updateFuncMap_[State::Pause] = [&](float deltaTime) {update_Pause(deltaTime); };
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::start()
{
	world_.Initialize();
	tutorialNumber_ = 0;
	isEnd_ = false;
	state_ = State::Play;
	pause_.initialize();
	std::shared_ptr<Field> field = std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
	world_.addField(field);
	std::shared_ptr<OverLookingCamera> camera = std::make_shared<OverLookingCamera>(&world_, "Camera", Vector3::Zero);
	world_.addCamera(camera);
	int playerNumber = 1;
	std::shared_ptr<TutorialPlayer> player = std::make_shared<TutorialPlayer>(&world_, "Player", Vector3::Up*15.0f, this);
	world_.addActor(ActorGroup::PLAYER, player);
	world_.getCamera()->setTarget(world_.findActor("Player"));
	world_.getCamera()->setFirstPos();

	std::shared_ptr<TutorialPoint> point1 = std::make_shared<TutorialPoint>(Vector3{ -50.0f,15.0f,60.0f });
	world_.addActor(ActorGroup::TUTORIAL, point1);
	std::shared_ptr<TutorialPoint> point2 = std::make_shared<TutorialPoint>(Vector3{ 60.0f,15.0f,60.0f });
	world_.addActor(ActorGroup::TUTORIAL, point2);
	std::shared_ptr<TutorialPoint> point3 = std::make_shared<TutorialPoint>(Vector3{ 0.0f,15.0f,-50.0f });
	world_.addActor(ActorGroup::TUTORIAL, point3);

	

	world_.getCanChangedTempoManager().setMusic(BGM_ID::STAGE1_BGM, 156.0f);
	changeState(State::TextDraw);

	world_.FindInitialize();

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
	text_.Draw();
	if (state_ == Pause)pause_.draw();

}

void TutorialScene::end()
{
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE();

}

void TutorialScene::changeState(State state) {

	if (state_ == state)return;//既にその状態なら遷移しない

							   //状態の終了処理を行う
	switch (state_)
	{
	case TextDraw:
		world_.getCanChangedTempoManager().startMusic();//音を再生
		break;
	case Play:
		break;
	case Pause:
		world_.restart();
		break;
	default:
		break;
	}

	//状態を変えて
	state_ = state;

	//対応した変更時処理を行う
	switch (state_)
	{
	case Reload: {
		end();
		start();
		break;
	}
	case TextDraw:
		tutorialNumber_++;
		if (tutorialNumber_ > 3) {
			isEnd_ = true;
			next_ = SceneType::SCENE_TITLE;
			return;
		}
		text_.Init("Lesson" + std::to_string(tutorialNumber_)+".txt", 51);

		world_.getCanChangedTempoManager().pauseMusic();//音を再生
		break;
	case Play:
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
		changeState(Play);
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
		if(state==GamePlayState::Reload)changeState(Reload);
		else changeState(Play);
	}

}

int TutorialScene::getTutorialNum() const
{
	return tutorialNumber_;
}

void TutorialScene::nextLesson()
{
	if(state_==Play)
		changeState(TextDraw);

}
