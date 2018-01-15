#pragma once
#include"Scene.h"
#include<array>

//リソース読み込み専用シーン
class LoadingScene:public Scene {
public:
	LoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//画像の読み込み
	void LoadSprite();
	//モデルの読み込み
	void LoadModel();
	//動画の読み込み
	void LoadMovie();
	//モデルの読み込み
	void LoadEffect();
	//文字フォントの読み込み
	void LoadFont();
	//BGMの読み込み
	void LoadBGM();
	//SEの読み込み
	void LoadSE();
	//シャドウマップの読み込み
	void LoadShadowMap();
	//その他ステージ等の読み込み
	void LoadEtcetera();

private:
	std::array<float, 3> posits_;

	float timeCount_;
	int keyCount_;
};