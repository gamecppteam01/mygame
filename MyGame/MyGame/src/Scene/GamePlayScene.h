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
//リソース読み込み専用シーン
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
	//標準ライトクラス
	StandardLight standardLight_;
	//ライトハンドルクラス
	LightHandle lightHandle_;
	int startCount_;
};