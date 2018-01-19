#pragma once
#include"../ScoreManager/ScoreData.h"
#include"../ScoreManager/ScoreManager.h"
#include"../Graphic/DxlibGraphic.h"
#include"../Actor/Player/Player.h"
#include"../World/IWorld.h"
#include"UI.h"

class ShowRankUI{
public:
	ShowRankUI(IWorld * world);
	void initialize() ;
	void update(float deltaTime) ;
	void draw() const ;

	void pause();
	void restart();

private:
	IWorld * world_;
	ScoreData* score_;
	Vector3 position_;
	int id_;
	bool pause_{ false };
};