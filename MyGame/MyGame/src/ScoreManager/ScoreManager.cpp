#include "ScoreManager.h"
#include<algorithm>
#include"../Actor/Actor.h"
#include"../Actor/Player/Player.h"
#include"../Actor/Enemy/BaseEnemy.h"

//�R���X�g���N�^
ScoreManager::ScoreManager(IWorld* world):
m_World(world){
	initialize();
}

//�f�X�g���N�^
ScoreManager::~ScoreManager(){
	m_ScoreDataList.clear();
	m_NumberList.clear();
}

//������
void ScoreManager::initialize(){
	m_ScoreDataList.clear();
	m_NumberList.clear();

	ActorPtr p = m_World->findActor("Player");
	if (p != nullptr) {
		std::shared_ptr<Player> player = std::static_pointer_cast<Player>(p);
		add(0, player->getPlayerNumber(), 1.0f, p);
		m_NumberList.push_back(player->getPlayerNumber());
	}

	std::list<ActorPtr> enemyList;
	m_World->findActors("Enemy", enemyList);
	for (auto& e : enemyList) {
		if (e == nullptr)continue;
		std::shared_ptr<BaseEnemy> enemy = std::static_pointer_cast<BaseEnemy>(e);
		add(0, enemy->getPlayerNumber(), 1.0f, e);
		m_NumberList.push_back(enemy->getPlayerNumber());
	}
}

//�L�����N�^�[�̒ǉ�
void ScoreManager::add(int score, int number ,float rate,const ActorPtr& target){
	m_ScoreDataList[number] = ScoreData(rate,score,number,target);
}

//�X�R�A�̉��Z
void ScoreManager::addScore(int number, int score){
	m_ScoreDataList[number].score_ += score * m_ScoreDataList[number].scoreRate_;
}

//�o�^����Ă���L��������Ԃ�
int ScoreManager::GetCharacterCount()const {
	return m_ScoreDataList.size();
}

//�L�����N�^�[�̃X�R�A��Ԃ�
int ScoreManager::GetCharacterScore(int number) {
	return m_ScoreDataList[number].score_;
}

//�{���̕ύX
void ScoreManager::ChangeScoreRate(const int number, const float rate) {
	m_ScoreDataList[number].scoreRate_ = rate;
}

//�ő�X�R�A��Ԃ�
int ScoreManager::getMaxScore() const{
	int maxScore = 0;
	for (auto n : m_NumberList) {
		if (maxScore < m_ScoreDataList.at(n).score_) {
			maxScore = m_ScoreDataList.at(n).score_;
		}
	}
	//maxScore = *std::max_element(m_ScoreList.begin(), m_ScoreList.end());
	return maxScore;
}
