#pragma once
#include"Scene.h"
#include<array>

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
	//����̓ǂݍ���
	void LoadMovie();
	//���f���̓ǂݍ���
	void LoadEffect();
	//�����t�H���g�̓ǂݍ���
	void LoadFont();
	//BGM�̓ǂݍ���
	void LoadBGM();
	//SE�̓ǂݍ���
	void LoadSE();
	//�V���h�E�}�b�v�̓ǂݍ���
	void LoadShadowMap();
	//���̑��X�e�[�W���̓ǂݍ���
	void LoadEtcetera();

private:
	std::array<float, 3> posits_;

	float timeCount_;
	int keyCount_;
};