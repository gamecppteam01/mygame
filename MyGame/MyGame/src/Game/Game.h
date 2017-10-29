#pragma once

#include "DxLib.h"
#include "Time.h"
#include "../Input/InputChecker.h"
#include "../Math/Math.h"
#include"../Camera/Camera.h"
#include"../Input/DualShock4Manager.h"
#include"../Graphic/EffekseerManager.h"

class Game {
protected:
	// コンストラクタ
	Game(const Vector2& screen_size = Vector2(800, 600), float rate = 1.0f, int window = TRUE, float fps = 60.0f) :
		mWidth(static_cast<int>(screen_size.x)), mHeight(static_cast<int>(screen_size.y)), mRate(rate), mWindow(window), mFps(fps) {
	}

public:
	// 実行
	int run() {
		// サイズ指定
		SetGraphMode(mWidth, mHeight, 32);
		// 描画倍率
		SetWindowSizeExtendRate(mRate);
		// ウインドウモードにするかどうか
		ChangeWindowMode(mWindow);
		SetUseDirect3DVersion(DX_DIRECT3D_9);
		//DXLib初期化処理
		if (DxLib_Init() == -1)return -1;//エラーが起きたら終了
		SetDrawScreen(DX_SCREEN_BACK);
		EffekseerManager::GetInstance().Initialize();
		start();

		// キーが押されるまでループします
		while (isRunning()) {
			etceteraUpdate();

			update();
			draw();

			frameEnd();
			//Time::GetInstance().draw_fps();
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
		}

		end();

		//DXLib使用終了処理
		DxLib_End();

		return 0;	//ソフト終了
	}

private:
	// 開始
	virtual void start() {}
	// 更新
	virtual void update() {}
	// 描画
	virtual void draw() {}
	//フレーム終了時処理
	virtual void frameEnd() {}
	// 終了
	virtual void end() {}
	// 実行中か
	virtual bool isRunning() { return (ProcessMessage() == 0 && ClearDrawScreen() == 0 && Keyboard::GetInstance().KeyStateUp(KEYCODE::ESC)); }

	void etceteraUpdate() {
		//deltaTimeの更新
		Time::GetInstance().update();
		//入力の更新
		InputChecker::GetInstance().Update();
		//DualShock4専用の入力更新
		DualShock4Manager::GetInstance().Update();

		EffekseerManager::GetInstance().Update();
	}
private:
	// コピー禁止
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	// ウィンドウの幅
	int mWidth;
	// ウィンドウの高さ
	int mHeight;
	// ウインドウの描画比率
	float mRate;
	// ウインドウモードか？
	int mWindow;
	// FPS
	float mFps;
};