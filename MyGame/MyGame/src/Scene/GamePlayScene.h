#pragma once
#include"Scene.h"
#include"../World/World.h"
#include "../UI/ComboGaugeUI.h"
#include"../ScoreManager/ScoreDisplay.h"
#include"../Effect/PlayerEffectDraw.h"
#include"../Light/StandardLight.h"
#include"../Light/LightHandle.h"

enum GamePlayState
{
	Start,
	Play,
	End,
	Pause
};
//���\�[�X�ǂݍ��ݐ�p�V�[��
class GamePlayScene :public Scene {
public:
	GamePlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;
	ScoreDisplay scoreDisplay_;
	GamePlayState state_;
	PlayerEffectDraw playerEffectDraw_;
	//�W�����C�g�N���X
	StandardLight standardLight_;
	//���C�g�n���h���N���X
	LightHandle lightHandle_;
	int startCount_;
};