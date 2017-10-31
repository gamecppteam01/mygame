#pragma once
#include "../Math/Math.h"
#include<list>
#include<map>
#include "../World/IWorld.h"
#include "../Actor/ActorPtr.h"
#include "ScoreRateManager.h"

//スコア情報一括管理構造体
struct ScoreData {
	ScoreData() {

	}
	ScoreData(float rate, int score, int playerNumber, const ActorPtr& target) :
		scoreRate_(rate), score_(score), playerNumber_(playerNumber), target_(target) {

	}
	//スコア倍率
	float scoreRate_;
	//得点
	int score_;
	//対象の出場番号
	int playerNumber_;
	//対象
	std::weak_ptr<Actor> target_;
};

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
	void add_Player(int score, int number, float rate ,const ActorPtr& target);
	//スコアの加算
	void addScore(int number, int score);
	//倍率の変更
	void ChangeScoreRate(const int number, const float rate);
	//登録されているキャラ数を返す
	int GetCharacterCount()const;
	//キャラクターのスコアを返す
	int GetCharacterScore(int number);
	//最大スコアを返す
	int getMaxScore() const;
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
};
