#pragma once
#include "../BaseEnemy.h"
#include "../../../ScoreManager/ScoreManager.h"
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

	enum class LightState {
		Extinction,
		CenterLighting,
		SpotLighting,
	};
	enum class RivalState {
		AttackMode,
		MoveMode,
		StepMode,
	};
public:
	Enemy_Rival();
	//コンストラクタ
	Enemy_Rival(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber)override;

private:
	virtual void JustStep() override{}
	//初期化
	void initialize();
	virtual void onMessage(EventMessage message, void * param) override;
	// 描画
	virtual void onDraw() const override;

	virtual void onShadowDraw() const override;

	virtual void updateNormal(float deltaTime)override;
	virtual void to_Normal()override;
	virtual void to_Step(Enemy_Animation anim) override;
	virtual void to_Attack(Enemy_Animation anim) override;

	//virtual void spin(float deltaTime)override;

	//周回ポイント一覧のうち最も近い点を求める
	int getNearestPoint(const Vector3 & position);
	void setNearestPoint();

private:

	void setNextPosition();

	void ExtinctionUpdate(float deltaTime);
	void CenterLightingUpdate(float deltaTime);
	void SpotLighting(float deltaTime);

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
	//スコアマネージャー
	ScoreManager* scoreManager_;
	//ライト座標
	Vector3 lightPosition_;
	//スタート座標
	Vector3 startPos_;

	//前の攻撃タイプ
	AttackType prevAttackType_;
	MethodTimer defAnimSetTimer_;
	//ペア数
	int count_{ 0 };
	//移動停止カウント
	int moveCount_{ 0 };
	//ステップカウント
	int stepCount_{ 0 };
	//移動タイマー
	float moveTimer_{ 0.0f };
	//停止タイマー
	float stopTimer_{ 0.0f };
	//ライトの状態
	LightState lightState_{ LightState::Extinction };
	//状態
	RivalState rivalState_{ RivalState::AttackMode };
	//前の状態
	RivalState prevRivalState_;

	std::map<LightState, std::function<void(float deltaTime)>> m_LightStateUpdateFunc;

};