#pragma once
#include"Scene.h"

class TutorialScene:public Scene {
public:
	TutorialScene();
	~TutorialScene();

	//�V�[���J�n���ɌĂяo�����(world�쐬�A�l�̏��������͂����ōs��)
	void start()override;
	//���t���[���Ăяo�����(�L�����N�^�[��world�̍X�V���͂����ōs��)
	void update(float deltaTime) override;
	//���t���[��update�̌�ɌĂяo�����(�`��͂����ōs���Aconst�Ȃ��߁Adraw���ŃO���[�o���ϐ��̒l��ύX������͏o���Ȃ�)
	void draw()const override;
	//�V�[����isEnd_�t���O��true�ɂȂ������ɌĂяo�����(�V�[���I�����̏����͂����ōs��)
	void end()override;

};
