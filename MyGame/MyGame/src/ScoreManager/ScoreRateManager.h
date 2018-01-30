#pragma once
#include"../World/IWorld.h"
#include<list>
#include"../Actor/Judge/JudgeBase.h"

class ScoreRataManager {
public:
	//コンストラクタ
	explicit ScoreRataManager(IWorld* world);
	//初期化
	void initialize();
	//計算結果の倍率を返す
	float getRata() const;
	//審査員を巡回する
	void Judge_Crawl(ActorPtr& target);
	//倍率計算(スポットライト含む)
	float mathScoreRata_All(const Vector3& target);
	//倍率計算(スポットライト含まない)
	float mathScoreRata_All_Not(const Vector3& target);

private:
	//審査員の集まり
	void Judge_Collect();

private:
	//ワールド
	IWorld*		m_World;
	//審査員のグループ
	using  s_Judge = std::shared_ptr<JudgeBase>;
	std::list<s_Judge> m_JudgeAll;		//スポットライト含む
	std::list<s_Judge> m_JudgeAll_Not;		//スポットライト含まない
	//倍率
	float m_Rata;
	//カウント
	int m_Count;
};
