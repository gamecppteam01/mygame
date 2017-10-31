#include "ScoreManager.h"
#include<algorithm>
#include"../Actor/Actor.h"
#include"../Actor/Player/Player.h"
#include"../Actor/Enemy/BaseEnemy.h"

//�R���X�g���N�^
ScoreManager::ScoreManager(IWorld* world):
m_World(world),m_RataManager(world){
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
	m_RataManager.initialize();

	ActorPtr p = m_World->findActor("Player");
	if (p != nullptr) {
		std::shared_ptr<Player> player = std::static_pointer_cast<Player>(p);
		add_Player(0, player->getPlayerNumber(), 1.0f, p);	//�I��̒ǉ�
		m_NumberList.push_back(player->getPlayerNumber());	//�I��ԍ����X�g�ɒǉ�
	}

	std::list<ActorPtr> enemyList;
	m_World->findActors("Enemy", enemyList);
	for (auto& e : enemyList) {
		if (e == nullptr)continue;
		std::shared_ptr<BaseEnemy> enemy = std::static_pointer_cast<BaseEnemy>(e);
		add_Player(0, enemy->getPlayerNumber(), 1.0f, e);	//�I��̒ǉ�
		m_NumberList.push_back(enemy->getPlayerNumber());	//�I��ԍ����X�g�ɒǉ�
	}
}

//�X�V
void ScoreManager::updata(float deltaTime) {
	for (auto n : m_NumberList) {
		//�R�����̔���̏���
		m_RataManager.Judge_Crawl(m_ScoreDataList.at(n).target_.lock());
		//�{���̕ύX
		ChangeScoreRate(n, m_RataManager.getRata());
	}
}

//�L�����N�^�[�̒ǉ�
void ScoreManager::add_Player(int score, int number ,float rate,const ActorPtr& target){
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

//1�ʂ��珇�ɓ�����ScoreData�^�̃��X�g��Ԃ�
void ScoreManager::getRankingList(std::list<ScoreData>& list) {
	int maxScore = 0;
	int score = 0;
	maxScore = getMaxScore();
	for (auto n : m_NumberList) {
		if (maxScore > m_ScoreDataList.at(n).score_ && score < m_ScoreDataList.at(n).score_) {
			score = m_ScoreDataList.at(n).score_;
		}
	}
}