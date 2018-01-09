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
//リソース読み込み専用シーン
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

	//ライトの設定関数
	void settingLight();
	//UI設定関数
	void settingUI();

private:
	//現在のステージ番号
	int stageNum_{ 1 };

	World world_;
	//ScoreDisplay scoreDisplay_;
	GamePlayState state_;
	PlayerEffectDraw playerEffectDraw_;
	//標準ライトクラス
	StandardLight standardLight_;
	//ライトハンドルクラス
	LightHandle lightHandle_;
	//フレームカウンター
	float freamCounter_{ 0.0f };
	bool isStart_;
	std::shared_ptr<SpecifiedStepManager> specifiedStepManager_;
	float timeCount_{ 3.0f };//スタート時のタイマー
	int currentCount_{ 4 };//スタートで到達したカウント
	PauseScreen pause_;

	MethodExecutor methodExecutor_;

	float timer_{ 0.0f };
	//状態毎更新map
	std::map<GamePlayState, std::function<void(float)>> updateFuncMap_;
};