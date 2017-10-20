#include "Judge_NPC.h"
#include"../../World/IWorld.h"
#include"../Body/BoundingCapsule.h"
#include"../ActorGroup.h"
#include"../../Graphic/Model.h"
#include"../../Math/Math.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Define.h"
#include<list>

//コンストラクタ
Judge_NPC::Judge_NPC(IWorld * world, const std::string & name, const Vector3 & position,float scope_angle)
	:Actor(world,name,position,	std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f))
	,m_Scope_angle(scope_angle),yaw(0.0f){
	initialize();
}

//初期化
void Judge_NPC::initialize() {
	m_Angle = 45.0f;
	m_Count = 0.0f;
	yaw = 1;
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
	m_State = Judge_State::Search;
	m_Timer = 0.0f;
}

//メッセージ処理
void Judge_NPC::onMessage(EventMessage message, void * param) {
}

//更新
void Judge_NPC::onUpdate(float deltaTime) {
	StateUpdate(deltaTime);
}

//描画
void Judge_NPC::onDraw() const {
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	std::list<ActorPtr> targets;
	world_->findActors("Enemy", targets);
	targets.push_back(world_->findActor("Player"));
	for (auto t : targets) {
		if (is_Scorp_Angle(t) == true && is_In_Distans(t) == true) {
			DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "視覚内");
		}
	}
}

//衝突処理
void Judge_NPC::onCollide(Actor & other) {
}

//状態更新
void Judge_NPC::StateUpdate(float deltaTime){
	switch (m_State)
	{
	case Judge_State::Search:
		SearchUpdate(deltaTime);
		break;
	case Judge_State::Regard:
		RegardUpdate(deltaTime);
		break;
	}
}

//探索更新
void Judge_NPC::SearchUpdate(float deltaTime){
	if (m_Count >= m_Angle || m_Count <= -m_Angle) {
		m_State = Judge_State::Regard;
		m_Timer = 3.0f;
		return;
	}
	rotation_ *= Matrix::CreateRotationY(yaw);
	m_Count += yaw;
}

//注視更新
void Judge_NPC::RegardUpdate(float deltaTime){
	if (m_Timer <= 0) {
		yaw *= -1;
		m_Count += yaw;
		m_State = Judge_State::Search;
	}
	m_Timer -= deltaTime;
}

//視野角内にいるか？
bool Judge_NPC::is_Scorp_Angle(ActorPtr& target) const
{
	//相手のベクトルの取得
	Vector3 V1 = target->position() - position_;
	V1.Normalize();	//正規化
	//自分の正面のベクトルの取得
	Vector3 V2 = rotation_.Backward();
	V2.Normalize();	//正規化

	//自分と相手のベクトルからなす角を取る
	float result = Vector3::Dot(V1, V2);
	result = MathHelper::ACos(result);

	//視野角内にいるか？
	if (result <= m_Scope_angle) {	return true; }
	return false;
}

//一定距離内にいるか？
bool Judge_NPC::is_In_Distans(ActorPtr & target) const
{
	float result;
	//ターゲットと自分の距離を求める
	result = Vector3::Distance(target->position(), position_);
	//自分とターゲットとの距離が一定以内だったら真
	if (result <= 50) {	return true; }
	return false;
}