#pragma once
#include"Scene.h"
#include"../World/World.h"
#include"Screen/PauseScreen.h"
#include"GamePlayState.h"
#include"../Graphic/TextScreen.h"
#include<queue>
#include<stack>
#include"../Light/StandardLight.h"
#include"../Light/LightHandle.h"

class TutorialPlayer;
class TutorialScene :public Scene {
private:
	enum State {
		Reload,
		Next,
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

	void nextTutorial();//�J�b�g�C���ƃe�L�X�g�`��̑J�ڐ�����肷��

	void nextLesson();//��ԑJ��

	void settingLight();

private:
	const float StopTime{ 3.0f };//��~����
	const float InTime{ 0.5f };//�J�b�g�C���̍Đ�����
	const float OutTime{ 0.5f };//�J�b�g�C���̍Đ�����
	float cutInTimer_{ 0.0f };//�J�b�g�C���̌��Đ�����
	std::queue<State> cutInNextState_;//�J�b�g�C���Đ���̏��
	std::queue<State> textNextState_;//�e�L�X�g��̏��
	SPRITE_ID currentCutIn_;//���݂̃J�b�g�C����ID
	std::stack<SPRITE_ID> cutInID_;//�J�b�g�C����ID�҂����X�g
	int tutorialNumber_;
	World world_;
	PauseScreen pause_;
	TextScreen text_;
	State state_;
	State prevState_;
	std::shared_ptr<TutorialPlayer> player_;
	std::map<State, std::function<void(float)>> updateFuncMap_;

	//�W�����C�g�N���X
	StandardLight standardLight_{};
	//���C�g�n���h���N���X
	LightHandle lightHandle_{};

	std::shared_ptr<Judgement_SpotLight> light_;
};
