#pragma once
#include "Scene.h"
#include "../ScoreManager/ScoreManager.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../World/IWorld.h"
#include "../World/World.h"
#include <list>

/* ���ʂƃX�R�A����ׂ�A�^�C�g���ɖ߂� */
/* ���ׂẴX�R�A���\�[�g���č~���ɉ�ʂɕ\������ */

class GameClearScene : public Scene {
public:
	GameClearScene();
	~GameClearScene() override;
	void start() override;
	void update(float deltaTime) override;
	void draw() const;
	void end() override;
		
private:
	//���[���h
	World world_;
	std::list<ScoreData> datas_;
};