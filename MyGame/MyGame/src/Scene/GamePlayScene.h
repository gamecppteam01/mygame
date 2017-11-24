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
	Pause,
	End,
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

	void update_Start(float deltaTime);
	void update_Play(float deltaTime);
	void update_Pause(float deltaTime);
	void update_End(float deltaTime);

	void changeState(GamePlayState state);

private:
	World world_;
	ScoreDisplay scoreDisplay_;
	GamePlayState state_;
	PlayerEffectDraw playerEffectDraw_;
	//標準ライトクラス
	StandardLight standardLight_;
	//ライトハンドルクラス
	LightHandle lightHandle_;
	//ライトテスト変数(終わり次第消します)
	float out_angle{ 1.0f }, in_angle{ 0.2f };
	float atten0{ 0.1f }, atten1{ 0.01f }, atten2{ 0.0f }, range{ 500.0f };

	//状態毎更新map
	std::map<GamePlayState, std::function<void(float)>> updateFuncMap_;
};