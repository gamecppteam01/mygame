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

	light_ = nullptr;

	world_.Initialize();
	settingLight();
	tutorialNumber_ = 1;
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
	
	//textNextState_.push(CutIn);//バトルダンスとは？
	//cutInNextState_.push(TextDraw);//バトルダンスについて
	//textNextState_.push(TextDraw);//移動について
	//textNextState_.push(Play);//移動させる
	changeState(State::TextDraw);

	world_.FindInitialize();

	text_.Reset();

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
	//ライトハンドルの全削除
	lightHandle_.deleteLightHandleAll();
}

void TutorialScene::changeState(State state) {

	//if (state_ == state)return;//既にその状態なら遷移しない

							   //状態の終了処理を行う
	switch (state_)
	{
	case TextDraw:
		//world_.getCanChangedTempoManager().restartMusic();//音を再生
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

	//状態を変えて
	prevState_ = state_;
	state_ = state;

	//対応した変更時処理を行う
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

		//world_.getCanChangedTempoManager().pauseMusic();//音を中断
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
	if (cutInTimer_ >= StopTime+ InTime+ OutTime) {
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
	switch (tutorialNumber_)
	{
	case 1: {
		//一番目のテキストが終わったらバトルダンスについてのカットイン
		if (prevState_ == State::TextDraw) {
			changeState(CutIn);
		}
		//テキスト終わった後にカットインもおわったらバトルダンスの説明へ
		else {
			tutorialNumber_++;
			changeState(TextDraw);
		}
		break;
	}
	case 2: {
		//説明が終わったら移動のカットイン
		if (prevState_ == State::TextDraw) {
			changeState(CutIn);
		}
		//カットインが終わったら移動の説明へ
		else {
			tutorialNumber_++;
			changeState(TextDraw);
		}
		break;
	}
	case 3: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			changeState(Play);//移動をやらせる
		}
		break;
	}
	case 4: {
		//説明が終わったらステップのカットイン
		if (prevState_ == State::TextDraw) {
			changeState(CutIn);
		}
		//カットインが終わったらステップの説明へ
		else {
			tutorialNumber_++;
			changeState(TextDraw);
		}
		break;
	}
	case 5: {
		tutorialNumber_++;
		changeState(TextDraw);//クォーターの説明へ
		break;
	}
	case 6: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			changeState(Play);//クォーターをやらせる
		}
		break;
	}
	case 7: {
		tutorialNumber_++;
		changeState(TextDraw);//クォーターの説明が終わったらターンへ
		break;
	}
	case 8: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			changeState(Play);//ターンをやらせる
		}
		break;
	}
	case 9: {
		tutorialNumber_++;
		changeState(TextDraw);//ハーフへ
		break;
	}
	case 10: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			changeState(Play);//ハーフをやらせる
		}
		break;
	}
	case 11: {
		tutorialNumber_++;
		changeState(TextDraw);//スピンへ
	}
	case 12: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			changeState(Play);//スピンをやらせる
		}
		break;
	}
	case 13: {
		//説明が終わったらライトのカットイン
		if (prevState_ == State::TextDraw) {
			changeState(CutIn);
		}
		//カットインが終わったらライトの説明へ
		else {
			tutorialNumber_++;
			changeState(TextDraw);
		}
		break;
	}
	case 14: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			light_ = std::make_shared<Judgement_SpotLight>(&world_, Vector3(0.0f, 2.0f, 0.0f), lightHandle_);
			world_.addActor(ActorGroup::NPC, light_);

			changeState(Play);//ライトにはいらせる
		}
		break;
	}
	case 15: {
		//説明が終わったら規定プログラムのカットイン
		if (prevState_ == State::TextDraw) {
			if(light_.use_count()>0)light_->dead();
			changeState(CutIn);
		}
		//カットインが終わったら規定プログラムの説明へ
		else {
			tutorialNumber_++;
			changeState(TextDraw);
		}
		break;
	}
	case 16: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			player_->initCheckStep();
			player_->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
			player_->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
			//player_->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
			
			player_->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Half});
			player_->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});
			//player_->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});

			changeState(Play);//規定プログラムをやらせる
		}
		break;
	}
	case 17: {
		//説明が終わったらコンボのカットイン
		if (prevState_ == State::TextDraw) {
			changeState(CutIn);
		}
		//カットインが終わったらコンボの説明へ
		else {
			tutorialNumber_++;
			changeState(TextDraw);
		}
		break;
	}
	case 18: {
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			player_->resetCombo();
			changeState(Play);//ポイントアップコンボをやらせる
		}
		break;
	}
	case 19: {
		tutorialNumber_++;
		changeState(TextDraw);//バーストコンボの説明
		break;
	}
	case 20:{
		if (prevState_ == Play) {
			//やってたらほめる
			tutorialNumber_++;
			changeState(TextDraw);
		}
		else {
			player_->resetCombo();
			changeState(Play);//バーストコンボをやらせる
		}
		break;
	}
	case 21: {
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
		cutInID_.push(cutinList[tutorialNumber_]);
		changeState(Next);
	}
}

void TutorialScene::settingLight()
{
	//標準ライトの設定
	standardLight_.initialize();
	standardLight_.changeLightTypeDir(Vector3(0.0f, -1.0f, 0.0f));
	standardLight_.setLightAmbientColor(Color(0.1f, 0.1f, 0.1f, 0.1f));
	standardLight_.setLghtSpecurColor(Color(0.5f, 0.5f, 0.5f, 0.5f));
	standardLight_.setLightDiffuseColor(Color(0.5f, 0.5f, 0.5f, 0.5f));

	//ライトハンドルの設定
	lightHandle_.setUsePixelLighting(true);
	lightHandle_.createSpotLightHandle("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 500.0f, 0.75f, 0.003f, 0.0f);
	lightHandle_.setLightAmbientColorHandle("Spot", Color(0.0f, 0.0f, 0.0f, 0.0f));
	lightHandle_.setLightDiffuseColorHandle("Spot", Color(0.7f, 0.7f, 0.2f, 1.0f));
	lightHandle_.setLightSpecuarColorHandle("Spot", Color(1.0f, 1.0f, 1.0f, 1.0f));
	//グローバルアンビエントの設定
	standardLight_.setGlobalAmbientLight(Color(0.5f, 0.5f, 0.5f, 0.5f));
	lightHandle_.setLightEnableHandle("Spot", false);

}
