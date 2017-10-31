#pragma once
#include"../World/IWorld.h"
#include<list>
#include"../Actor/Judge/JudgeBase.h"

class ScoreRataManager {
public:
	//コンストラクタ
	ScoreRataManager(IWorld* world);
	//初期化
	void initialize();
	//計算結果の倍率を返す
	float getRata() const;
	//審査員を巡回する
	void Judge_Crawl(ActorPtr& target);

private:
	//審査員の集まり
	void Judge_Group();

private:
	//ワールド
	IWorld*		m_World;
	//審査員のグループ
	using  s_Judge = std::shared_ptr<JudgeBase>;
	std::list<s_Judge> m_JudgeGroup;
	//倍率
	float m_Rata;
	//カウント
	int m_Count;
};
