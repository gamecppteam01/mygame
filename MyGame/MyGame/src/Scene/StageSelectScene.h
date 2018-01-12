#pragma once
#include"Scene.h"
#include<vector>
#include<array>
#include"../Light/StandardLight.h"
#include"../UI/Model_Animation_UI/Model_Animation_UI.h"

//�V�[���e���v���[�g(���O�����͊e���ύX���Ďg�����A�V�[���N���X���p�����Ă���)
class StageSelectScene :public Scene {
	enum FADE{
		FADE_OUT,
		CHANGE_MODEL,
		FADE_IN,

		NONE,
	};
public:
	//�R���X�g���N�^(�萔�̐ݒ蓙�͂����ōs���A���������т𗘗p���ĕK���ϐ���1�x���������鎖)
	StageSelectScene();
	//�f�X�g���N�^(�R���e�i�̌�n�����A�Q�[���I�����ɕK�v�ȏ����͂����ōs��)
	~StageSelectScene();
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
	void ChangeBGM();
	void ChangeModel();

private:
	//����V�[�����ŕK�v�Ȋ֐��͂����ɍ��

	StandardLight light_;
	Model_Animation_UI anim_UI_Mgr_;

	std::vector<std::vector<std::array<MODEL_ID,2>>> UI_Models_{
		{ std::array<MODEL_ID,2>{MODEL_ID::BALANCEENEMY_MODEL,MODEL_ID::BALANCEENEMY_BULLET_MODEL },std::array<MODEL_ID,2>{MODEL_ID::PLAYER_MODEL,MODEL_ID::PLAYER_BULLET_MODEL } },
		{ std::array<MODEL_ID,2>{MODEL_ID::PLAYER_MODEL,MODEL_ID::PLAYER_BULLET_MODEL },std::array<MODEL_ID,2>{MODEL_ID::BALANCEENEMY_MODEL,MODEL_ID::BALANCEENEMY_BULLET_MODEL }, std::array<MODEL_ID,2>{MODEL_ID::RIVALENEMY_MODEL,MODEL_ID::RIVALENEMY_BULLET_MODEL } },
		{ std::array<MODEL_ID,2>{MODEL_ID::RIVALENEMY_MODEL,MODEL_ID::RIVALENEMY_BULLET_MODEL } ,std::array<MODEL_ID,2>{MODEL_ID::BALANCEENEMY_MODEL,MODEL_ID::BALANCEENEMY_BULLET_MODEL },std::array<MODEL_ID,2>{MODEL_ID::PLAYER_MODEL,MODEL_ID::PLAYER_BULLET_MODEL } },
		{ std::array<MODEL_ID,2>{MODEL_ID::DUMMY_MODEL,MODEL_ID::DUMMY_MODEL } }
	};

	int cursor_{ 0 };	//�J�[�\���ʒu
	int current_cursor_;//���݂̃J�[�\���ʒu
	int prev_cursor_;	//�O�̏�Ԃ̃J�[�\���ʒu

	int prevCursor_{ 0 };

	int sinCount_{ 0 };
	float t;
	float Ypos;

	float timer_{ 0.0f };
	float timer2_{ 0.0f };

	int count_{ 0 };

	Vector3 cameraPos_{ Vector3::Zero };
	Vector3 cameraPos2_{ Vector3(0,0,-1000) };
	Vector3 cameraTarget_{ Vector3(0,0,-1) };
	Vector3 cameraTarget2_{ Vector3(1.0f, 0.0f, 1.0f) };
	FADE fade_{ NONE };
};