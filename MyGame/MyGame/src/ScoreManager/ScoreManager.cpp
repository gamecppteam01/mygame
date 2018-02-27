#include "ScoreManager.h"
#include<algorithm>
#include"../Actor/Actor.h"
#include"../Actor/Player/Player.h"
#include"../Actor/Judge/Judgement_SpotLight/Judgement_SpotLight.h"
#include"../Actor/Enemy/BaseEnemy.h"
#include"../DataManager/DataManager.h"

//コンストラクタ
ScoreManager::ScoreManager(IWorld* world):
m_World(world),m_RataManager(world){
	initialize();
}

//デストラクタ
ScoreManager::~ScoreManager(){
	m_ScoreDataList.clear();
	m_NumberList.clear();
}

//初期化
void ScoreManager::initialize(){
	m_ScoreDataList.clear();
	m_NumberList.clear();
	m_RataManager.initialize();
	timeCount_ = 0;

	ActorPtr p = m_World->findActor("Player");
	if (p != nullptr) {
		std::shared_ptr<Player> player = std::static_pointer_cast<Player>(p);
		add_Player(0, player->getPlayerNumber(), 1.0f,1, p);//選手の追加
		m_NumberList.push_back(player->getPlayerNumber());	//選手番号リストに追加
		m_FirstData = m_ScoreDataList[player->getPlayerNumber()];
	}

	std::list<ActorPtr> enemyList;
	m_World->findActors("Enemy", enemyList);
	for (auto& e : enemyList) {
		if (e == nullptr)continue;
		std::shared_ptr<BaseEnemy> enemy = std::static_pointer_cast<BaseEnemy>(e);
		add_Player(0, enemy->getPlayerNumber(), 1.0f, 1, e, enemy->getModelID(), enemy->getBulletModelID());	//選手の追加
		m_NumberList.push_back(enemy->getPlayerNumber());	//選手番号リストに追加
	}
}

//更新
void ScoreManager::updata(float deltaTime) {

	timeCount_++;
	//20フレームに1回スコア計算を行う
	if (timeCount_ < 20)return;

	timeCount_ = 0;

	for (auto n : m_NumberList) {
		//審査員の判定の巡回
		m_RataManager.Judge_Crawl(m_ScoreDataList.at(n).target_.lock());
		//倍率の変更
		ChangeScoreRate(n, m_RataManager.getRata());
	}
}

//キャラクターの追加
void ScoreManager::add_Player(int score, int number ,float rate, int rank,const ActorPtr& target, MODEL_ID manModel, MODEL_ID womanModel){
	m_ScoreDataList[number] = ScoreData(score,number, rate, rank,target,manModel,womanModel);
}

//スコアの加算
void ScoreManager::addScore(int number, int score){
	m_ScoreDataList[number].score_ += score * m_ScoreDataList[number].scoreRate_;

	if (m_FirstData.score_ < m_ScoreDataList[number].score_) {
		m_FirstData = m_ScoreDataList[number];
	}
}

//登録されているキャラ数を返す
int ScoreManager::GetCharacterCount()const {
	return m_ScoreDataList.size();
}

//キャラクターのスコアを返す
int ScoreManager::GetCharacterScore(int number) {
	return m_ScoreDataList[number].score_;
}
float ScoreManager::GetCharacterScoreRate(int number) {
	return m_ScoreDataList[number].scoreRate_;
}

//倍率の変更
void ScoreManager::ChangeScoreRate(const int number, const float rate) {
	m_ScoreDataList[number].scoreRate_ = rate;
}

//倍率計算(スポットライト含む)
float ScoreManager::mathScoreRata_All(const Vector3 & target)
{
	return m_RataManager.mathScoreRata_All(target);
}

//倍率計算(スポットライト含まない)
float ScoreManager::mathScoreRata_All_Not(const Vector3 & target)
{
	return m_RataManager.mathScoreRata_All_Not(target);
}

//最大スコアを返す
int ScoreManager::getMaxScore() const{
	return m_FirstData.score_;
}

ScoreData* ScoreManager::getScoreData(int num)
{
	return &m_ScoreDataList.at(num);
}

//一位の選手のスコアデータを返す
ScoreData ScoreManager::getFirst() {
	return m_FirstData;
}

//指定の倍率を返す
float ScoreManager::getRata(const int number) const {
	return m_ScoreDataList.at(number).scoreRate_;
}

//list<ScoreData>型のリストを渡す
void ScoreManager::getScoreDataList(std::list<ScoreData*>& list) {
	for (auto n : m_NumberList) {
		list.push_back(&m_ScoreDataList[n]);
	}
}

void ScoreManager::getScoreDataMap(std::map<int, ScoreData*> &map){
	std::for_each(m_ScoreDataList.begin(), m_ScoreDataList.end(), [&map](auto& data) {map[data.first] = &data.second; });
}

//1位から順に入ったScoreData型のリストを返す
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

std::list<int> ScoreManager::getPlayerNumberList()
{
	std::list<int> numbers;
	ActorPtr light = m_World->findActor("SpotLight");
	std::shared_ptr<Judgement_SpotLight> spot = std::static_pointer_cast<Judgement_SpotLight>(light);
	for (int n : m_NumberList) {
		if (spot->In_Range(m_ScoreDataList[n].target_.lock()) == true) {
			numbers.push_back(m_ScoreDataList[n].playerNumber_);
		}
	}
	return numbers;
}

ScoreData * ScoreManager::getNoticePlayer()
{
	ScoreData data;
	for (auto& d : m_ScoreDataList) {
		if (d.second.notice_ == true) {
			data = d.second;
			break;
		}
	}
	return &data;
}
