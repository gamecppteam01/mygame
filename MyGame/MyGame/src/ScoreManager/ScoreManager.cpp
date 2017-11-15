#include "ScoreManager.h"
#include<algorithm>
#include"../Actor/Actor.h"
#include"../Actor/Player/Player.h"
#include"../Actor/Enemy/BaseEnemy.h"
#include"../DataManager/DataManager.h"

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
	timeCount_ = 0;

	ActorPtr p = m_World->findActor("Player");
	if (p != nullptr) {
		std::shared_ptr<Player> player = std::static_pointer_cast<Player>(p);
		add_Player(0, player->getPlayerNumber(), 1.0f,1, p);//�I��̒ǉ�
		m_NumberList.push_back(player->getPlayerNumber());	//�I��ԍ����X�g�ɒǉ�
	}

	std::list<ActorPtr> enemyList;
	m_World->findActors("Enemy", enemyList);
	for (auto& e : enemyList) {
		if (e == nullptr)continue;
		std::shared_ptr<BaseEnemy> enemy = std::static_pointer_cast<BaseEnemy>(e);
		add_Player(0, enemy->getPlayerNumber(), 1.0f,1, e);	//�I��̒ǉ�
		m_NumberList.push_back(enemy->getPlayerNumber());	//�I��ԍ����X�g�ɒǉ�
	}
}

//�X�V
void ScoreManager::updata(float deltaTime) {

	//timeCount_++;
	//20�t���[����1��X�R�A�v�Z���s��
	//if (timeCount_ < 20)return;

	//timeCount_ = 0;

	for (auto n : m_NumberList) {
		//�R�����̔���̏���
		m_RataManager.Judge_Crawl(m_ScoreDataList.at(n).target_.lock());
		//�{���̕ύX
		ChangeScoreRate(n, m_RataManager.getRata());
	}
}

//�L�����N�^�[�̒ǉ�
void ScoreManager::add_Player(int score, int number ,float rate, int rank,const ActorPtr& target){
	m_ScoreDataList[number] = ScoreData(score,number, rate, rank,target);
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
float ScoreManager::GetCharacterScoreRate(int number) {
	return m_ScoreDataList[number].scoreRate_;
}

//�{���̕ύX
void ScoreManager::ChangeScoreRate(const int number, const float rate) {
	m_ScoreDataList[number].scoreRate_ = rate;
}

//�{���v�Z(�X�|�b�g���C�g�܂�)
float ScoreManager::mathScoreRata_All(const Vector3 & target)
{
	return m_RataManager.mathScoreRata_All(target);
}

//�{���v�Z(�X�|�b�g���C�g�܂܂Ȃ�)
float ScoreManager::mathScoreRata_All_Not(const Vector3 & target)
{
	return m_RataManager.mathScoreRata_All_Not(target);
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

//��ʂ̑I��̃X�R�A�f�[�^��Ԃ�
ScoreData ScoreManager::getFirst() {
	ScoreData data;
	for (auto n : m_NumberList) {
		if (getMaxScore() == m_ScoreDataList[n].score_) {
			data = m_ScoreDataList[n];
		}
	}
	return data;
}

//�w��̔{����Ԃ�
float ScoreManager::getRata(const int number) const {
	return m_ScoreDataList.at(number).scoreRate_;
}

//list<ScoreData>�^�̃��X�g��n��
void ScoreManager::getScoreDataList(std::list<ScoreData>& list) {
	for (auto n : m_NumberList) {
		list.push_back(m_ScoreDataList[n]);
	}
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