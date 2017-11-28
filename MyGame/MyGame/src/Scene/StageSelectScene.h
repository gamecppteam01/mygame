#pragma once
#include"Scene.h"
#include<vector>

//シーンテンプレート(名前部分は各自変更して使う事、シーンクラスを継承している)
class StageSelectScene :public Scene {
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
	//自作シーン内で必要な関数はここに作る

	int cursor_{ 0 };//カーソル位置

	int prevCursor_{ 0 };
private:
	//遷移先リスト
	const std::vector<std::pair<SceneType,int>> ButtonList{
		{SceneType::SCENE_GAMEPLAY,1},
		{SceneType::SCENE_GAMEPLAY,2},
		{SceneType::SCENE_GAMEPLAY,3},
		{SceneType::SCENE_TITLE   ,1}
	};
};