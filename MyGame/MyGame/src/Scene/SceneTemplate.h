#pragma once
#include"Scene.h"

//�V�[���e���v���[�g(���O�����͊e���ύX���Ďg�����A�V�[���N���X���p�����Ă���)
class SceneTemplate :public Scene {
public:
	//�R���X�g���N�^(�萔�̐ݒ蓙�͂����ōs���A���������т𗘗p���ĕK���ϐ���1�x���������鎖)
	SceneTemplate();
	//�f�X�g���N�^(�R���e�i�̌�n�����A�Q�[���I�����ɕK�v�ȏ����͂����ōs��)
	~SceneTemplate();
	//�V�[���J�n���ɌĂяo�����(world�쐬�A�l�̏��������͂����ōs��)
	void start()override;
	//���t���[���Ăяo�����(�L�����N�^�[��world�̍X�V���͂����ōs��)
	void update(float deltaTime) override;
	//���t���[��update�̌�ɌĂяo�����(�`��͂����ōs���Aconst�Ȃ��߁Adraw���ŃO���[�o���ϐ��̒l��ύX������͏o���Ȃ�)
	void draw()const override;
	//�V�[����isEnd_�t���O��true�ɂȂ������ɌĂяo�����(�V�[���I�����̏����͂����ōs��)
	void end()override;
	//���̑��K�v�Ȋ֐�������Ή��ɍ��


private:
	//����V�[�����ŕK�v�Ȋ֐��͂����ɍ��

};