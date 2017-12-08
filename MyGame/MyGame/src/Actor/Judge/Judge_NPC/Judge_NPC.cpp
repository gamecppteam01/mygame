#include "Judge_NPC.h"
#include"../../../World/IWorld.h"
#include"../../Body/BoundingCapsule.h"
#include"../../ActorGroup.h"
#include"../../../Graphic/Model.h"
#include"../../../Math/Math.h"
#include"../../../Graphic/DebugDraw.h"
#include"../../../Define.h"
#include<list>

//コンストラクタ
Judge_NPC::Judge_NPC(IWorld * world, const Vector3 & position,const Matrix& rotation)
	:JudgeBase(world,"Judge",position){
	rotation_ = rotation;
	initialize();
}

//初期化
void Judge_NPC::initialize() {
	m_Angle = 45.0f;
	m_Count = 0.0f;
	yaw = 1;
	modelHandle_ = MODEL_ID::JUDGE_MODEL;
	animation_.SetHandle(Model::GetInstance().GetHandle(modelHandle_));
	animation_.ChangeAnim(0);
	m_State = Judge_State::Search;
	m_Timer = 0.0f;
}

//メッセージ処理
void Judge_NPC::onMessage(EventMessage message, void * param) {
}

//更新
void Judge_NPC::onUpdate(float deltaTime) {
	animation_.Update(1.0f);
	StateUpdate(deltaTime);
}

//描画
void Judge_NPC::onDraw() const {
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));
}

//衝突処理
void Judge_NPC::onCollide(Actor & other) {
}

//判定
bool Judge_NPC::Judgement(ActorPtr& target) {
	if (is_Scorp_Angle(target) == true && is_In_Distans(target) == true) {
		return true;
	}
	return false;
}

bool Judge_NPC::Judgement(const Vector3 & target)
{
	Vector2 myPos = Vector2(position_.x, position_.z);
	Vector2 targetPos = Vector2(target.x, target.z);
	if (is_Scorp_Angle(target) == true && Vector2::Distance(myPos, targetPos) <= 50.0f) {
		return true;
	}
	return false;
}

//角度の取得
float Judge_NPC::getAngle() const
{
	return m_Angle;
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