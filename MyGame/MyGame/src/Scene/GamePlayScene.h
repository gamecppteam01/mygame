#pragma once
#include"Scene.h"
#include"../World/World.h"
#include "../UI/ComboGaugeUI.h"
#include"../ScoreManager/ScoreDisplay.h"
#include"../Effect/PlayerEffectDraw.h"
#include"../Light/StandardLight.h"
#include"../Light/LightHandle.h"
#include"Screen/PauseScreen.h"
#include"GamePlayState.h"
#include"../Graphic/TextScreen.h"
#include"../Method/MethodExecutor.h"

class SpecifiedStepManager;
//���\�[�X�ǂݍ��ݐ�p�V�[��
class GamePlayScene :public Scene {
public:
	GamePlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;


private:

	void update_Reload(float deltaTime);
	void update_Start(float deltaTime);
	void update_Play(float deltaTime);
	void update_Pause(float deltaTime);
	void update_End(float deltaTime);
	void update_Round(float deltaTime);

	void changeState(GamePlayState state);

	//���C�g�̐ݒ�֐�
	void settingLight();
	//UI�ݒ�֐�
	void settingUI();

private:
	//���݂̃X�e�[�W�ԍ�
	int stageNum_{ 1 };

	World world_;
	//ScoreDisplay scoreDisplay_;
	GamePlayState state_;
	PlayerEffectDraw playerEffectDraw_;
	//�W�����C�g�N���X
	StandardLight standardLight_;
	//���C�g�n���h���N���X
	LightHandle lightHandle_;
	//�t���[���J�E���^�[
	float freamCounter_{ 0.0f };
	bool isStart_;
	std::shared_ptr<SpecifiedStepManager> specifiedStepManager_;
	float timeCount_{ 3.0f };//�X�^�[�g���̃^�C�}�[
	int currentCount_{ 4 };//�X�^�[�g�œ��B�����J�E���g
	PauseScreen pause_;

	MethodExecutor methodExecutor_;

	float timer_{ 0.0f };
	//��Ԗ��X�Vmap
	std::map<GamePlayState, std::function<void(float)>> updateFuncMap_;
};