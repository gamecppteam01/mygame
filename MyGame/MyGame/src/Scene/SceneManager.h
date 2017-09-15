#pragma once
#include<map>
#include<memory>
#include"SceneType.h"
class Scene;

//�V�[���̊Ǘ����s���AGame�y�т��̔h���N���X�ŗ��p����
class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void start();
	void update(float deltaTime);
	void draw();
	//�V�[�����I�����Ă��邩���m�F���A�K�v�ł���Ύ��̃V�[���ɑJ�ڂ���
	void checkIsEnd();
	//���̃V�[���֑J�ڂ���
	void next();


private:
	//�V�[���ꗗ
	std::map<SceneType, std::shared_ptr<Scene>> scenes_;
	//���݂̃V�[��
	SceneType currentScene_;
};