#include "SceneTemplate.h"

//�R���X�g���N�^(�萔�̐ݒ蓙�͂����ōs���A���������т𗘗p���ĕK���ϐ���1�x���������鎖)

SceneTemplate::SceneTemplate() {
	//�V�[���̓f�t�H���g��isEnd(bool)��next_(SceneType)�������Ă���
	//next_�̑J�ڐ�͕K���l��ݒ肷�鎖
	//��) next_=SceneType::SCENE_GAMEPLAY;
}

//�f�X�g���N�^(�R���e�i�̌�n�����A�Q�[���I�����ɕK�v�ȏ����͂����ōs��)

SceneTemplate::~SceneTemplate() {

}

//�V�[���J�n���ɌĂяo�����(world�쐬�A�l�̏��������͂����ōs��)

void SceneTemplate::start() {

}

//���t���[���Ăяo�����(�L�����N�^�[��world�̍X�V���͂����ōs��)

void SceneTemplate::update(float deltaTime) {

}

//���t���[��update�̌�ɌĂяo�����(�`��͂����ōs���Aconst�Ȃ��߁Adraw���ŃO���[�o���ϐ��̒l��ύX������͏o���Ȃ�)

void SceneTemplate::draw() const {

}

//�V�[����isEnd_�t���O��true�ɂȂ������ɌĂяo�����(�V�[���I�����̏����͂����ōs��)

void SceneTemplate::end() {

}
