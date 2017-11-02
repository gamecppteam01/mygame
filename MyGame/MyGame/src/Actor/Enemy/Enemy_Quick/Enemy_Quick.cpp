#include "Enemy_Quick.h"
#include "../EnemyBullet.h"
#include "../../ActorGroup.h"
#include "../../../World/IWorld.h"
#include "../../../Graphic/Model.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerBullet.h"
#include "../../../Graphic/DebugDraw.h"
#include "../../../ScoreManager/ScoreManager.h"
#include "../../../Math/Random.h"
#include "../../../ScoreManager/ScoreMap.h"



//相手に気づく範囲
static const float noticeDistance = 30.0f;

//コンストラクタ
Enemy_Quick::Enemy_Quick(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body)
:BaseEnemy(world,name,position,playerNumber,body){
	target_ = world_->findActor("Player");
	m_Timer = 5.0f;
}

//ステップ通知時の処理
void Enemy_Quick::JustStep() {
	int rand = Random::GetInstance().Range(1, 10);
	if (rand <= 6) {
		//ターン
		world_->getCanChangedScoreManager().addScore(playerNumber_, 200);
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Turn);
	}
	else {
		//クォーター
		world_->getCanChangedScoreManager().addScore(playerNumber_, 100);
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::KnockBack);
	}
}

void Enemy_Quick::updateNormal(float deltaTime){
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	searchTarget(deltaTime);
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;
	m_Timer--;
}

void Enemy_Quick::to_Normal(){

}

//索敵
void Enemy_Quick::searchTarget(float deltaTime) {
	//ターゲットが存在しなければ索敵無効
	if (target_ == nullptr)return;
	//ターゲットの位置を検索
	Vector3 targetPos = target_->position();
	//ターゲット方向のベクトル
	Vector3 toTarget = targetPos - position_;
	//ターゲットとの距離を求める
	float distance = Vector3::Distance(position_, targetPos);

	//ターゲットとの距離が範囲内だったら
	if (distance < noticeDistance) {
		//ターゲットの逆方向に逃げる
		velocity_ = -toTarget.Normalize();
		m_Timer = 5.0f;
	}
	else if(distance > noticeDistance && m_Timer <= 0){
		velocity_ = Vector3::Zero;
	}
}