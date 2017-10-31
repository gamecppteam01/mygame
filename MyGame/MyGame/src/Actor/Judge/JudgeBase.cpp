#include "JudgeBase.h"
#include "../../World/IWorld.h"
#include"../Body/BoundingCapsule.h"
#include"../ActorGroup.h"
#include"../../Graphic/Model.h"
#include"../../Math/Math.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Define.h"
#include<list>

//�R���X�g���N�^
JudgeBase::JudgeBase(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr& body)
:Actor(world, name, position, body) {
}

//������
void JudgeBase::initialize(){
}

//���b�Z�[�W����
void JudgeBase::onMessage(EventMessage message, void * param){
}

//�X�V
void JudgeBase::onUpdate(float deltaTime){
}

//�`��
void JudgeBase::onDraw() const{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));
}

//�Փˏ���
void JudgeBase::onCollide(Actor & other){
}

//����p���ɂ��邩�H
bool JudgeBase::is_Scorp_Angle(ActorPtr& target, float angle) const
{
	//����̃x�N�g���̎擾
	Vector3 V1 = target->position() -position_;
	V1.Normalize();	//���K��
					//�����̐��ʂ̃x�N�g���̎擾
	Vector3 V2 = rotation_.Backward();
	V2.Normalize();	//���K��

					//�����Ƒ���̃x�N�g������Ȃ��p�����
	float result = Vector3::Dot(V1, V2);
	result = MathHelper::ACos(result);

	//����p���ɂ��邩�H
	if (result <= angle) { return true; }
	return false;
}

//��苗�����ɂ��邩�H
bool JudgeBase::is_In_Distans(ActorPtr & target,float distance) const
{
	float result;
	//�^�[�Q�b�g�Ǝ����̋��������߂�
	result = Vector3::Distance(target->position(), position_);
	//�����ƃ^�[�Q�b�g�Ƃ̋��������ȓ���������^
	if (result <= distance) { return true; }
	return false;
}
