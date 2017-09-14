#pragma once
#include"Scene.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class LoadingScene:public Scene {
public:
	LoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//�摜�̓ǂݍ���
	void LoadSprite();
	//���f���̓ǂݍ���
	void LoadModel();
	//�����t�H���g�̓ǂݍ���
	void LoadFont();
	//BGM�̓ǂݍ���
	void LoadBGM();
	//SE�̓ǂݍ���
	void LoadSE();
	//���̑��X�e�[�W���̓ǂݍ���
	void LoadEtcetera();

};