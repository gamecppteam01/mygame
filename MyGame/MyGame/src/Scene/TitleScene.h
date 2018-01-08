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
	//三段階
	third,
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
	int brightCount_{ 0 };
private:
	//カーソルの位置及びボタンの位置リスト
	const std::vector<std::pair<Vector2, SceneType>> cursorPoses{
		{ Vector2{ 450.0f,400.f },SceneType::SCENE_TUTORIAL },
		{ Vector2{ 450.0f,525.f },SceneType::SCENE_STAGESELECT },
		{ Vector2{ 450.0f,650.f },SceneType::SCENE_EXIT }//ゲーム終了(遷移先はダミー)
	};
	//カーソルの位置
	const std::vector<std::pair<Vector2, bool>> cursorPoses2{
		{ Vector2{450.0f,525.0f},true},
		{ Vector2{ 450.0f,650.0f },false }
	};
};