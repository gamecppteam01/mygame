#pragma once
#include "Scene.h"

#include"../Math/Vector3.h"
#include"../Math/Vector2.h"
#include"../Define.h"

#include<vector>
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
	//カーソル位置
	int cursor_{ 0 };

	Vector3 scale{ Vector3::One };
	//画面状態
	TitleState titleState_;
	//サイン波
	int SinCount_;
	float temp;

private:
	//カーソルの位置及びボタンの位置リスト
	const std::vector<std::pair<Vector2, SceneType>> cursorPoses{
		{Vector2{ 300.0f,500.f },SceneType::SCENE_GAMEPLAY},
		{Vector2{ 300.0f,600.f },SceneType::SCENE_EXIT }//ゲーム終了(遷移先はダミー)
	};
};