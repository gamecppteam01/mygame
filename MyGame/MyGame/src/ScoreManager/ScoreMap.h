#pragma once
#include"../Math/Vector3.h"
#include"../Math/TwoDimensionalArray.h"
#include"../Method/MethodTimer.h"
#include<memory>
#include<vector>

class IWorld;
class JudgeBase;
class Judgement_SpotLight;

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
		bool alreadyChecked_{ false };
	};
public:
	explicit ScoreMap(IWorld* world);
	~ScoreMap();
	void initialize();
	//未作成
	void update(float deltaTime);
	//周囲のポイントで一番スコア倍率の高い物を返す
	Vector3 getNextPoint(const Vector3& point,float* resultRate=nullptr);

	Vector3 getNearestBonusPoint(const Vector3& point);

	std::vector<Vector3> getRoundPoint();
private:
	//倍率検索
	void mathScoreRate();
	void mathScoreRate(ScorePoint& point);
private:
	IWorld* world_;
	//スコアレート計算タイマー
	MethodTimer mathScoreRateTimer_;
	//スコア位置の
	TwoDimensionalArray<ScorePoint> points_{
		4,4,
		ScorePoint{ Vector3(-120.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(120.0f,0.0f,-120.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(120.0f,0.0f,-40.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(120.0f,0.0f,40.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(120.0f,0.0f,120.0f) }
	};
	//審査員リスト
	std::vector<std::shared_ptr<JudgeBase>> judges_;
	std::shared_ptr<Judgement_SpotLight> spotLight_;

};