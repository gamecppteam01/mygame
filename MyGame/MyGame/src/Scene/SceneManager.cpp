#include "SceneManager.h"
#include"Scenes.h"
#include"../Fade/FadePanel.h"

//ローディングシーンから開始
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_LOADING), fadesp_(){
}

SceneManager::~SceneManager() {
	scenes_.clear();
}

void SceneManager::init()
{
	//利用するシーンを作成し、シーンリストに追加する
	scenes_[SceneType::SCENE_LOADING] = std::make_shared<LoadingScene>();
	scenes_[SceneType::SCENE_TITLE] = std::make_shared<TitleScene>();
	scenes_[SceneType::SCENE_STAGESELECT] = std::make_shared<StageSelectScene>();
	scenes_[SceneType::SCENE_GAMEPLAY] = std::make_shared<GamePlayScene>();
	scenes_[SceneType::SCENE_CLEAR] = std::make_shared<GameClearScene>();
	scenes_[SceneType::SCENE_GAMEOVER] = std::make_shared<GameOverScene>();
	//scenes_[SceneType::SCENE_CREDIT] = std::make_shared<CreditScene>();
	scenes_[SceneType::SCENE_TUTORIAL] = std::make_shared<TutorialScene>();

}

void SceneManager::start() {
	scenes_[currentScene_]->start();
}

void SceneManager::update(float deltaTime) {
	if (FadePanel::GetInstance().IsAction())return;
	fadesp_.update(deltaTime);
	if (fadesp_.isActive())return;
	scenes_[currentScene_]->update(deltaTime);
}

void SceneManager::draw() {
	scenes_[currentScene_]->draw();
	fadesp_.draw();
}

//シーンが終了しているかを確認し、必要であれば次のシーンに遷移する

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next();

}

//次のシーンへ遷移する

void SceneManager::next() {
	if (FadePanel::GetInstance().IsAction())return;
	if (fadesp_.isActive())return;

	//音声を終了して
	//Sound::GetInstance().StopBGM();
	//Sound::GetInstance().StopSE();
	
	if (scenes_[currentScene_]->nextScene() == SceneType::SCENE_GAMEPLAY||
		scenes_[currentScene_]->nextScene() == SceneType::SCENE_CLEAR) {
		fadesp_.addCallBack([&] {		
			//シーンを終了して
			scenes_[currentScene_]->end();
			SceneType nextScene = scenes_[currentScene_]->nextScene();
			currentScene_ = nextScene;
			//次のシーンを開始する
			scenes_[currentScene_]->baseInit();
			scenes_[currentScene_]->start();

		});
		fadesp_.start();
		return;
	}
	FadePanel::GetInstance().AddCollBack([&] {
		//シーンを終了して
		scenes_[currentScene_]->end();
		SceneType nextScene = scenes_[currentScene_]->nextScene();
		currentScene_ = nextScene;
		//次のシーンを開始する
		scenes_[currentScene_]->baseInit();
		scenes_[currentScene_]->start();
		
		FadePanel::GetInstance().FadeIn();

	});
	FadePanel::GetInstance().FadeOut();
}
