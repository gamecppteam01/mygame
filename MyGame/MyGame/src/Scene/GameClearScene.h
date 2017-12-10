#pragma once
#include "Scene.h"
#include "../ScoreManager/ScoreManager.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../World/IWorld.h"
#include "../World/World.h"
#include <list>
#include"Screen/ResultScoreDraw.h"

/* 順位とスコアを並べる、タイトルに戻る */
/* すべてのスコアをソートして降順に画面に表示する */

class GameClearScene : public Scene {
public:
	GameClearScene();
	~GameClearScene() override;
	void start() override;
	void update(float deltaTime) override;
	void draw() const;
	void end() override;
		
private:
	std::list<ScoreData> datas_;

	int cursor_{ 0 };

	int sinCount_;
	ResultScoreDraw score_;
	//カーソルの位置及びボタンの位置リスト
	const std::vector<std::pair<Vector2, SceneType>> cursorPoses{
		{ Vector2{ 450.0f,500.f },SceneType::SCENE_GAMEPLAY },
		{ Vector2{ 450.0f,625.f },SceneType::SCENE_TITLE }
	};
};