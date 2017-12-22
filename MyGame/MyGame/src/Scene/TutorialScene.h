#pragma once
#include"Scene.h"
#include"../World/World.h"
#include"Screen/PauseScreen.h"
#include"GamePlayState.h"
#include"../Graphic/TextScreen.h"

class TutorialPlayer;
class TutorialScene :public Scene {
private:
	enum State {
		Reload,
		TextDraw,
		CutIn,
		Play,
		Pause
	};

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

	void changeState(State state);

	void update_textDraw(float deltaTime);
	void update_Play(float deltaTime);
	void update_Pause(float deltaTime);
	void update_CutIn(float deltaTime);

	int getTutorialNum()const;

	void nextLesson();//��ԑJ��
private:
	const float CutInTime{ 2.0f };//�J�b�g�C���̍Đ�����
	float cutInTimer_{ 0.0f };//�J�b�g�C���̌��Đ�����
	State cutInNextState_;//�J�b�g�C���Đ���̏��
	SPRITE_ID cutInID_;//�J�b�g�C����ID
	int tutorialNumber_;
	World world_;
	PauseScreen pause_;
	TextScreen text_;
	State state_;
	std::shared_ptr<TutorialPlayer> player_;
	std::map<State, std::function<void(float)>> updateFuncMap_;

};
