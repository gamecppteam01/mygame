#include "ScoreRateManager.h"

//�R���X�g���N�^
ScoreRataManager::ScoreRataManager(IWorld* world)
:m_World(world){
}

//������
void ScoreRataManager::initialize(){
	Judge_Group();
}

//�v�Z���ʂ̔{����Ԃ�
float ScoreRataManager::getRata() const{
	return m_Rata;
}

//�R�����̏W�܂�
void ScoreRataManager::Judge_Group(){
	m_JudgeGroup.clear();
	std::list<ActorPtr> target;
	m_World->findActors("Judge", target);
	std::shared_ptr<JudgeBase> judge;
	for (auto t : target) {
		judge = std::static_pointer_cast<JudgeBase>(t);
		m_JudgeGroup.push_back(judge);
	}
}

//�R���������񂷂�
void ScoreRataManager::Judge_Crawl(ActorPtr& target){
	m_Rata = 0.0f;
	m_Count = 0;
	for (auto j : m_JudgeGroup) {
		if (j->Judgement(target) == true) {
			m_Rata = 0.2f;
			m_Count++;
		}
	}
	m_Rata = 1.0f + (m_Rata * m_Count);
}
