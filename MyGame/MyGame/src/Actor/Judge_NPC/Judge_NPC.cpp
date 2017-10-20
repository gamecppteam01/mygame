#include "Judge_NPC.h"
#include"../../World/IWorld.h"
#include"../Body/BoundingCapsule.h"
#include"../ActorGroup.h"
#include"../../Graphic/Model.h"
#include"../../Math/Math.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Define.h"
#include<list>

//�R���X�g���N�^
Judge_NPC::Judge_NPC(IWorld * world, const std::string & name, const Vector3 & position,float scope_angle)
	:Actor(world,name,position,	std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f))
	,m_Scope_angle(scope_angle),yaw(0.0f){
	initialize();
}

//������
void Judge_NPC::initialize() {
	m_Angle = 45.0f;
	m_Count = 0.0f;
	yaw = 1;
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
	m_State = Judge_State::Search;
	m_Timer = 0.0f;
}

//���b�Z�[�W����
void Judge_NPC::onMessage(EventMessage message, void * param) {
}

//�X�V
void Judge_NPC::onUpdate(float deltaTime) {
	StateUpdate(deltaTime);
}

//�`��
void Judge_NPC::onDraw() const {
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	std::list<ActorPtr> targets;
	world_->findActors("Enemy", targets);
	targets.push_back(world_->findActor("Player"));
	for (auto t : targets) {
		if (is_Scorp_Angle(t) == true && is_In_Distans(t) == true) {
			DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "���o��");
		}
	}
}

//�Փˏ���
void Judge_NPC::onCollide(Actor & other) {
}

//��ԍX�V
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

//�T���X�V
void Judge_NPC::SearchUpdate(float deltaTime){
	if (m_Count >= m_Angle || m_Count <= -m_Angle) {
		m_State = Judge_State::Regard;
		m_Timer = 3.0f;
		return;
	}
	rotation_ *= Matrix::CreateRotationY(yaw);
	m_Count += yaw;
}

//�����X�V
void Judge_NPC::RegardUpdate(float deltaTime){
	if (m_Timer <= 0) {
		yaw *= -1;
		m_Count += yaw;
		m_State = Judge_State::Search;
	}
	m_Timer -= deltaTime;
}

//����p���ɂ��邩�H
bool Judge_NPC::is_Scorp_Angle(ActorPtr& target) const
{
	//����̃x�N�g���̎擾
	Vector3 V1 = target->position() - position_;
	V1.Normalize();	//���K��
	//�����̐��ʂ̃x�N�g���̎擾
	Vector3 V2 = rotation_.Backward();
	V2.Normalize();	//���K��

	//�����Ƒ���̃x�N�g������Ȃ��p�����
	float result = Vector3::Dot(V1, V2);
	result = MathHelper::ACos(result);

	//����p���ɂ��邩�H
	if (result <= m_Scope_angle) {	return true; }
	return false;
}

//��苗�����ɂ��邩�H
bool Judge_NPC::is_In_Distans(ActorPtr & target) const
{
	float result;
	//�^�[�Q�b�g�Ǝ����̋��������߂�
	result = Vector3::Distance(target->position(), position_);
	//�����ƃ^�[�Q�b�g�Ƃ̋��������ȓ���������^
	if (result <= 50) {	return true; }
	return false;
}