#include "ScoreRateManager.h"

//�R���X�g���N�^
ScoreRataManager::ScoreRataManager(IWorld* world)
:m_World(world),m_Count(0),m_Rata(0.0f){
}

//������
void ScoreRataManager::initialize(){
	Judge_Collect();
}

//�v�Z���ʂ̔{����Ԃ�
float ScoreRataManager::getRata() const{
	return m_Rata;
}

//�R�����̏W�܂�
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
	//�X�|�b�g���C�g�̒ǉ�
	auto lightPtr = m_World->findActor("SpotLight");
	if(lightPtr!=nullptr)m_JudgeAll.push_back(std::static_pointer_cast<JudgeBase>(lightPtr));
}

//�R���������񂷂�
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

//�{���v�Z(�X�|�b�g���C�g�܂�)
float ScoreRataManager::mathScoreRata_All(const Vector3& target) {
	float rata = 1.0f;
	for (auto j : m_JudgeAll) {
		if (j->Judgement(target) == true) {
			rata += 0.2f;
		}
	}
	return rata;
}

//�{���v�Z(�X�|�b�g���C�g�܂܂Ȃ�)
float ScoreRataManager::mathScoreRata_All_Not(const Vector3& target){
	float rata = 1.0f;
	for (auto j : m_JudgeAll_Not) {
		if (j->Judgement(target) == true) {
			rata += 0.2f;
		}
	}
	return rata;
}