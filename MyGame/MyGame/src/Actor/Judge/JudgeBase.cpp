#include "JudgeBase.h"
#include "../../World/IWorld.h"
#include"../Body/BoundingCapsule.h"
#include"../ActorGroup.h"
#include"../../Graphic/Model.h"
#include"../../Math/Math.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Define.h"
#include<list>

//コンストラクタ
JudgeBase::JudgeBase(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr& body)
:Actor(world, name, position, body) {
}

//初期化
void JudgeBase::initialize(){
}

//メッセージ処理
void JudgeBase::onMessage(EventMessage message, void * param){
}

//更新
void JudgeBase::onUpdate(float deltaTime){
}

//描画
void JudgeBase::onDraw() const{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));
}

//衝突処理
void JudgeBase::onCollide(Actor & other){
}

//視野角内にいるか？
bool JudgeBase::is_Scorp_Angle(ActorPtr& target, float angle) const
{
	//相手のベクトルの取得
	Vector3 V1 = target->position() -position_;
	V1.Normalize();	//正規化
					//自分の正面のベクトルの取得
	Vector3 V2 = rotation_.Backward();
	V2.Normalize();	//正規化

					//自分と相手のベクトルからなす角を取る
	float result = Vector3::Dot(V1, V2);
	result = MathHelper::ACos(result);

	//視野角内にいるか？
	if (result <= angle) { return true; }
	return false;
}

//一定距離内にいるか？
bool JudgeBase::is_In_Distans(ActorPtr & target,float distance) const
{
	float result;
	//ターゲットと自分の距離を求める
	result = Vector3::Distance(target->position(), position_);
	//自分とターゲットとの距離が一定以内だったら真
	if (result <= distance) { return true; }
	return false;
}
