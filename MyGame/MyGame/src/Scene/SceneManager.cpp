#include "SceneManager.h"
#include"Scenes.h"
#include"../Fade/FadePanel.h"

//���[�f�B���O�V�[������J�n
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_LOADING), fadesp_(){
}

SceneManager::~SceneManager() {
	scenes_.clear();
}

void SceneManager::init()
{
	//���p����V�[�����쐬���A�V�[�����X�g�ɒǉ�����
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

//�V�[�����I�����Ă��邩���m�F���A�K�v�ł���Ύ��̃V�[���ɑJ�ڂ���

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next();

}

//���̃V�[���֑J�ڂ���

void SceneManager::next() {
	if (FadePanel::GetInstance().IsAction())return;
	if (fadesp_.isActive())return;

	//�������I������
	//Sound::GetInstance().StopBGM();
	//Sound::GetInstance().StopSE();
	
	if (scenes_[currentScene_]->nextScene() == SceneType::SCENE_GAMEPLAY||
		scenes_[currentScene_]->nextScene() == SceneType::SCENE_CLEAR) {
		fadesp_.addCallBack([&] {		
			//�V�[�����I������
			scenes_[currentScene_]->end();
			SceneType nextScene = scenes_[currentScene_]->nextScene();
			currentScene_ = nextScene;
			//���̃V�[�����J�n����
			scenes_[currentScene_]->baseInit();
			scenes_[currentScene_]->start();

		});
		fadesp_.start();
		return;
	}
	FadePanel::GetInstance().AddCollBack([&] {
		//�V�[�����I������
		scenes_[currentScene_]->end();
		SceneType nextScene = scenes_[currentScene_]->nextScene();
		currentScene_ = nextScene;
		//���̃V�[�����J�n����
		scenes_[currentScene_]->baseInit();
		scenes_[currentScene_]->start();
		
		FadePanel::GetInstance().FadeIn();

	});
	FadePanel::GetInstance().FadeOut();
}
