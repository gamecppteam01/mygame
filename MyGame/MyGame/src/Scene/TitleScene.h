#pragma once
#include "Scene.h"

#include"../Math/Vector3.h"

enum TitleState
{
	//初期状態
	first,
	//二段階
	second,
};

class TitleScene : public Scene {
public:
	//コンストラクタ
	TitleScene();
	//デストラクタ
	~TitleScene() override;
	//開始
	void start() override;
	//更新
	void update(float deltaTime) override;
	//描画
	void draw() const override;
	//終了
	void end() override;

private:
	//
	int Counter_;
	int handle;
	Vector3 scale{ Vector3::One };
	//画面状態
	TitleState titleState_;
	//サイン波
	int SinCount_;
	float temp;
	float Cursol_;
};