#pragma once
#include"../Math/Vector3.h"
#include"../Math/TwoDimensionalArray.h"
#include<memory>
#include<vector>

class IWorld;
class Judge_NPC;

class ScoreMap {
private:

public:
	//スコア倍率検索ポイント
	struct ScorePoint
	{
		ScorePoint(Vector3 position = Vector3::Zero,float rate = 1.0f) :rate_(rate), position_(position) {
		}

		float rate_;
		Vector3 position_;
	};
public:
	explicit ScoreMap(IWorld* world);
	~ScoreMap();
	void initialize();
	//未作成
	void update(float deltaTime);
	//倍率検索
	void searchScoreRate();

private:
	IWorld* world_;
	//スコア位置の
	TwoDimensionalArray<ScorePoint> points_{
		4,4,
		ScorePoint{ Vector3(-120.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,-120.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,-40.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,40.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,120.0f) }
	};
	//審査員リスト
	std::vector<std::shared_ptr<Judge_NPC>> judges_;

};