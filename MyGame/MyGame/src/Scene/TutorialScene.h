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
#include"../Graphic/Movie.h"
#include"Screen/TutorialMovie.h"
#include"../UI/DrawAlphaSprite.h"

class TutorialPlayer;
class TutorialScene :public Scene {
private:
	enum State {
		Reload,
		Next,
		TextDraw,
		CutIn,
		Play,
		Pause,
		DrawSprite,
	};

public:
	TutorialScene();
	~TutorialScene();

	//シーン開始時に呼び出される(world作成、値の初期化等はここで行う)
	void start()override;
	//毎フレーム呼び出される(キャラクターやworldの更新等はここで行う)
	void update(float deltaTime) override;
	//毎フレームupdateの後に呼び出される(描画はここで行う、constなため、draw内でグローバル変数の値を変更したりは出来ない)
	void draw()const override;
	//シーンのisEnd_フラグがtrueになった時に呼び出される(シーン終了時の処理はここで行う)
	void end()override;

	void changeState(State state);

	void update_textDraw(float deltaTime);
	void update_Play(float deltaTime);
	void update_Pause(float deltaTime);
	void update_CutIn(float deltaTime);
	void update_DrawSprite(float deltaTime);
	
	int getTutorialNum()const;

	void nextTutorial();//カットインとテキスト描画の遷移先を決定する

	void nextLesson();//状態遷移

	void settingLight();

	void nextTutorialCount();

private:
	const float StopTime{ 2.0f };//停止時間
	const float InTime{ 0.5f };//カットインの再生時間
	const float OutTime{ 0.5f };//カットインの再生時間
	float cutInTimer_{ 0.0f };//カットインの現再生時間
	std::queue<State> cutInNextState_;//カットイン再生後の状態
	std::queue<State> textNextState_;//テキスト後の状態
	SPRITE_ID currentCutIn_;//現在のカットインのID
	std::stack<SPRITE_ID> cutInID_;//カットインのID待ちリスト
	int tutorialNumber_;
	World world_;
	PauseScreen pause_;
	TextScreen text_;
	State state_;
	State prevState_;
	std::shared_ptr<TutorialPlayer> player_;
	std::map<State, std::function<void(float)>> updateFuncMap_;
	TutorialMovie movie_;

	int tutorialTiming{ 0 };

	//標準ライトクラス
	StandardLight standardLight_{};
	//ライトハンドルクラス
	LightHandle lightHandle_{};

	std::shared_ptr<Judgement_SpotLight> light_;

	DrawAlphaSprite haveSprite_;
};
