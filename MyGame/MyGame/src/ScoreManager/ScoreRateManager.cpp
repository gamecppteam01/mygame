#include "ScoreRateManager.h"

//コンストラクタ
ScoreRataManager::ScoreRataManager(IWorld* world)
:m_World(world),m_Count(0),m_Rata(0.0f){
}

//初期化
void ScoreRataManager::initialize(){
	Judge_Collect();
}

//計算結果の倍率を返す
float ScoreRataManager::getRata() const{
	return m_Rata;
}

//審査員の集まり
void ScoreRataManager::Judge_Collect(){
	m_JudgeAll.clear();
	m_JudgeAll_Not.clear();
	std::list<ActorPtr> target;
	m_World->findActors("Judge", target);
	std::shared_ptr<JudgeBase> judge;
	for (auto t : target) {
		judge = std::static_pointer_cast<JudgeBase>(t);
		m_JudgeAll.push_back(judge);
		m_JudgeAll_Not.push_back(judge);
	}
	//スポットライトの追加
	auto lightPtr = m_World->findActor("SpotLight");
	if(lightPtr!=nullptr)m_JudgeAll.push_back(std::static_pointer_cast<JudgeBase>(lightPtr));
}

//審査員を巡回する
void ScoreRataManager::Judge_Crawl(ActorPtr& target){
	m_Rata = 0.0f;
	m_Count = 0;
	for (auto j : m_JudgeAll) {
		if (j->Judgement(target) == true) {
			m_Rata = 0.2f;
			m_Count++;
		}
	}
	m_Rata = 1.0f + (m_Rata * m_Count);
}

//倍率計算(スポットライト含む)
float ScoreRataManager::mathScoreRata_All(const Vector3& target) {
	float rata = 1.0f;
	for (auto j : m_JudgeAll) {
		if (j->Judgement(target) == true) {
			rata += 0.2f;
		}
	}
	return rata;
}

//倍率計算(スポットライト含まない)
float ScoreRataManager::mathScoreRata_All_Not(const Vector3& target){
	float rata = 1.0f;
	for (auto j : m_JudgeAll_Not) {
		if (j->Judgement(target) == true) {
			rata += 0.2f;
		}
	}
	return rata;
}