#include "SceneManager.h"
#include"Scenes.h"

//���[�f�B���O�V�[������J�n
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_LOADING) {
	//���p����V�[�����쐬���A�V�[�����X�g�ɒǉ�����
	scenes_[SceneType::SCENE_LOADING]  = std::make_shared<LoadingScene>();
	scenes_[SceneType::SCENE_TITLE]    = std::make_shared<TitleScene>();
	scenes_[SceneType::SCENE_GAMEPLAY] = std::make_shared<GamePlayScene>();
	scenes_[SceneType::SCENE_CLEAR]    = std::make_shared<GameClearScene>();
	scenes_[SceneType::SCENE_GAMEOVER] = std::make_shared<GameOverScene>();
	scenes_[SceneType::SCENE_CREDIT]   = std::make_shared<CreditScene>();
}

SceneManager::~SceneManager() {
	scenes_.clear();
}

void SceneManager::start() {
	scenes_[currentScene_]->start();
}

void SceneManager::update(float deltaTime) {
	scenes_[currentScene_]->update(deltaTime);
}

void SceneManager::draw() {
	scenes_[currentScene_]->draw();
}

//�V�[�����I�����Ă��邩���m�F���A�K�v�ł���Ύ��̃V�[���ɑJ�ڂ���

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next();

}

//���̃V�[���֑J�ڂ���

void SceneManager::next() {
	//�V�[�����I������
	scenes_[currentScene_]->end();
	SceneType nextScene = scenes_[currentScene_]->nextScene();
	currentScene_ = nextScene;
	//���̃V�[�����J�n����
	scenes_[currentScene_]->baseInit();
	scenes_[currentScene_]->start();
}
