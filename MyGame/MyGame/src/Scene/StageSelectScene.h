#pragma once
#include"Scene.h"
#include<vector>
#include<array>
#include"../Light/StandardLight.h"
#include"../UI/Model_Animation_UI/Model_Animation_UI.h"

//シーンテンプレート(名前部分は各自変更して使う事、シーンクラスを継承している)
class StageSelectScene :public Scene {
	enum FADE{
		FADE_OUT,
		CHANGE_MODEL,
		FADE_IN,

		NONE,
	};
public:
	//コンストラクタ(定数の設定等はここで行う、初期化並びを利用して必ず変数を1度初期化する事)
	StageSelectScene();
	//デストラクタ(コンテナの後始末等、ゲーム終了時に必要な処理はここで行う)
	~StageSelectScene();
	//シーン開始時に呼び出される(world作成、値の初期化等はここで行う)
	void start()override;
	//毎フレーム呼び出される(キャラクターやworldの更新等はここで行う)
	void update(float deltaTime) override;
	//毎フレームupdateの後に呼び出される(描画はここで行う、constなため、draw内でグローバル変数の値を変更したりは出来ない)
	void draw()const override;
	//シーンのisEnd_フラグがtrueになった時に呼び出される(シーン終了時の処理はここで行う)
	void end()override;
	//その他必要な関数があれば下に作る

private:
	void ChangeBGM();
	void ChangeModel();

private:
	//自作シーン内で必要な関数はここに作る

	StandardLight light_;
	Model_Animation_UI anim_UI_Mgr_;

	std::vector<std::vector<std::array<MODEL_ID,2>>> UI_Models_{
		{ std::array<MODEL_ID,2>{MODEL_ID::BALANCEENEMY_MODEL,MODEL_ID::BALANCEENEMY_BULLET_MODEL },std::array<MODEL_ID,2>{MODEL_ID::PLAYER_MODEL,MODEL_ID::PLAYER_BULLET_MODEL } },
		{ std::array<MODEL_ID,2>{MODEL_ID::PLAYER_MODEL,MODEL_ID::PLAYER_BULLET_MODEL },std::array<MODEL_ID,2>{MODEL_ID::BALANCEENEMY_MODEL,MODEL_ID::BALANCEENEMY_BULLET_MODEL }, std::array<MODEL_ID,2>{MODEL_ID::RIVALENEMY_MODEL,MODEL_ID::RIVALENEMY_BULLET_MODEL } },
		{ std::array<MODEL_ID,2>{MODEL_ID::RIVALENEMY_MODEL,MODEL_ID::RIVALENEMY_BULLET_MODEL } ,std::array<MODEL_ID,2>{MODEL_ID::BALANCEENEMY_MODEL,MODEL_ID::BALANCEENEMY_BULLET_MODEL },std::array<MODEL_ID,2>{MODEL_ID::PLAYER_MODEL,MODEL_ID::PLAYER_BULLET_MODEL } },
		{ std::array<MODEL_ID,2>{MODEL_ID::DUMMY_MODEL,MODEL_ID::DUMMY_MODEL } }
	};

	int cursor_{ 0 };	//カーソル位置
	int current_cursor_;//現在のカーソル位置
	int prev_cursor_;	//前の状態のカーソル位置

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