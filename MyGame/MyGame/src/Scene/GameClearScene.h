#pragma once
#include "Scene.h"
#include "../ScoreManager/ScoreManager.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../World/IWorld.h"
#include "../World/World.h"

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
	//ワールド
	World world_;
	std::list<ScoreData> datas_;
	int sinCount_;
	float timer_;
};