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
	ScoreManager() = default;
	explicit ScoreManager(IWorld* world);
	//デストラクタ
	~ScoreManager();
	//初期化
	void initialize();
	//更新
	void updata(float deltaTime);
	//選手の追加
	void add_Player(int score, int number, float rate ,int rank ,const ActorPtr& target, MODEL_ID manModel = MODEL_ID::PLAYER_MODEL, MODEL_ID womanModel = MODEL_ID::PLAYER_BULLET_MODEL);
	//スコアの加算
	void addScore(int number, int score);
	//倍率の変更
	void ChangeScoreRate(const int number, const float rate);
	//倍率計算(スポットライト含む)
	float mathScoreRata_All(const Vector3& target);
	//倍率計算(スポットライト含まない)
	float mathScoreRata_All_Not(const Vector3& target);
	//登録されているキャラ数を返す
	int GetCharacterCount()const;
	//キャラクターのスコアを返す
	int GetCharacterScore(int number);
	//キャラクターのスコア倍率を返す
	float GetCharacterScoreRate(int number);
	//最大スコアを返す
	int getMaxScore() const;
	ScoreData* getScoreData(int num);
	//一位の選手のスコアデータを返す
	ScoreData getFirst();
	//指定の倍率を返す
	float getRata(const int number) const;
	//list<ScoreData>型のリストを渡す
	void getScoreDataList(std::list<ScoreData*>& list);
	//
	void getScoreDataMap(std::map<int, ScoreData*> &map);
	//1位から順に入ったScoreData型のリストを返す
	void getRankingList(std::list<ScoreData>& list);
	//センターライト内に入っている選手番号のリストを返す
	std::list<int> getPlayerNumberList();
	//スポットライトを勝ち取った選手のデータを返す
	ScoreData* getNoticePlayer();

private:
	//ワールド
	IWorld* m_World;
	//倍率管理クラス
	ScoreRataManager m_RataManager;
	//スコアデータリスト
	std::map<int, ScoreData> m_ScoreDataList;
	//スコアリスト
	std::list<int> m_NumberList;
	int timeCount_;
	//1位の選手データ
	ScoreData m_FirstData;
};
