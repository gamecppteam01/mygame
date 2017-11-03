#pragma once
#include "../Math/Math.h"
#include<list>
#include<map>
#include "../World/IWorld.h"
#include "../Actor/ActorPtr.h"
#include "ScoreRateManager.h"
#include "ScoreData.h"


//スコアマネージャー
class ScoreManager {
public:
	//コンストラクタ
	ScoreManager(IWorld* world);
	//デストラクタ
	~ScoreManager();
	//初期化
	void initialize();
	//更新
	void updata(float deltaTime);
	//選手の追加
	void add_Player(int score, int number, float rate ,int rank ,const ActorPtr& target);
	//スコアの加算
	void addScore(int number, int score);
	//倍率の変更
	void ChangeScoreRate(const int number, const float rate);
	//登録されているキャラ数を返す
	int GetCharacterCount()const;
	//キャラクターのスコアを返す
	int GetCharacterScore(int number);
	//キャラクターのスコア倍率を返す
	int GetCharacterScoreRate(int number);
	//最大スコアを返す
	int getMaxScore() const;
	//一位の選手のスコアデータを返す
	ScoreData getFirst();
	//指定の倍率を返す
	float getRata(const int number) const;
	//list<ScoreData>型のリストを渡す
	void getScoreDataList(std::list<ScoreData>& list);
	//1位から順に入ったScoreData型のリストを返す
	void getRankingList(std::list<ScoreData>& list);

private:
	//ワールド
	IWorld* m_World;
	//倍率管理クラス
	ScoreRataManager m_RataManager;
	//スコアデータリスト
	std::map<int, ScoreData> m_ScoreDataList;
	//スコアリスト
	std::list<int> m_NumberList;
	//カウント
	int m_Count;
	int timeCount_;
};
