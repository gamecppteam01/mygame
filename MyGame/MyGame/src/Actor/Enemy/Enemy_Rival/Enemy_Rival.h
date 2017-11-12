#pragma once
#include "../BaseEnemy.h"
#include<queue>

class Enemy_Rival : public BaseEnemy {
private:
	enum class chooseAttackTargetMode {
		NotAttack,//通常時
		AttackMove,//攻撃対象に近づく
		Attack,//攻撃
		Return,//元の位置に戻る
		Step,//ステップする
		StepMove//ステップ位置に行く
	};
public:
	//コンストラクタ
	Enemy_Rival(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	// 描画
	virtual void onDraw() const override;

	//ステップ通知時の処理
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;
	virtual void updateTrack(float deltaTime)override;
	virtual void to_Normal()override;
	virtual void to_Track()override;
	virtual void to_Attack(BaseEnemy::Enemy_Animation anim)override;
	//周回ポイント一覧のうち最も近い点を求める
	int getNearestPoint(const Vector3 & position);

private:
	//Track時専用のステップ更新
	void justStepTrack();
	//Trackの次モードへの移行
	void toNextStepTrackMode(chooseAttackTargetMode nextMode);

	//攻撃対象が存在している場合
	void chooseStepAttackTarget(const ActorPtr& player);
	//プレイヤーが1位だったら
	void chooseStepAttackTopPlayer(const ActorPtr& player, const Vector3 basePos);
	bool chooseStepIsAttack();

	void setNextPosition();

	//転倒カウントのセット
	virtual void setCountDown();
private:
	//次のポイント
	int nextPoint_{ 0 };

	//狙う場所
	Vector3 targetPos_{ Vector3::Zero };
	//攻撃対象を定めるか
	chooseAttackTargetMode chooseAttackTargetMode_{ chooseAttackTargetMode::NotAttack };
	//攻撃対象の初期位置
	Vector3 attackTargetDefaultPos_{ Vector3::Zero };
	//攻撃時の自身の初期位置
	Vector3 attackStartDefaultPos_{ Vector3::Zero };
	//選手群
	std::list<std::weak_ptr<Actor>> players_;
	//stepAnimのキー番号リスト
	std::queue<int> stepQueue_;
	//ステージ周回ポイント配列
	std::vector<Vector3> roundPoint_;

	MethodTimer defAnimSetTimer_;
};