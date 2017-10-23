#pragma once
#include"../Math/Vector2.h"

class IWorld;

class ScoreMap {
public:
	//スコア倍率検索ポイント
	struct ScorePoint
	{
		ScorePoint(float rate = 1.0f, Vector2 position = Vector2::Zero) :rate_(rate), position_(position) {
		}

		float rate_;
		Vector2 position_;
	};
public:
	ScoreMap(IWorld* world);
	void initialize();
	void update(float deltaTime);
	

private:
	IWorld* world_;
};