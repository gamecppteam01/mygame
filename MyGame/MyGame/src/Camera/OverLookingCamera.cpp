#include "OverLookingCamera.h"
#include"Camera.h"
#include"../Graphic/Model.h"
#include"../Actor/Dummy/BetweenPositionActor.h"

//�Ώۂ����둤�ɗ���鋗��
static const float backwardLength = 3.0f;
//�Ώۂ���㑤�ɗ���鋗��
static const float upLength = 150.0f;

OverLookingCamera::OverLookingCamera(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Actor(world, name, position, body), target_(nullptr), targetTranslate_(Vector3::Zero)
{
}

void OverLookingCamera::setTarget(ActorPtr & target)
{
	target_ = target;
}

void OverLookingCamera::onMessage(EventMessage message, void * param)
{
}

void OverLookingCamera::onUpdate(float deltaTime)
{
	Vector3 targetPos = Vector3::Zero;
	if (target_ != nullptr) {
		//��U�Ώۂ̈ʒu�����ɂ���
		Vector3 nextPos= target_->position();

		//�J������ǉ��ň�����
		float addDistance = 0.0f;
		if (target_->getName() == "Point") {
			addDistance = std::static_pointer_cast<BetweenPositionActor>(target_)->getDistance()*0.5f;
		}
		//y���Œ肷��
		nextPos.y = upLength+ addDistance;

		//�J�������g�̈ʒu�́A�Ώۂ̈ʒu����J��������萔�������ʒu�ɒu��
		position_ = Vector3::Lerp(nextPos, position_, 0.9f);
		//�^�[�Q�b�g�̈ʒu��Ώۂ̈ʒu�ɐݒ�ݒ�
		targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength*10.0f);
		targetPos.y = 0.0f;
		//�ꉞy���Œ肵����
		position_.y = upLength+ addDistance;
		//z���Œ�l��������
		position_.z -= backwardLength;
	}



	Camera::GetInstance().Position.Set(position_);

	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(rotation_.Up());
	//Camera::GetInstance().SetRotation(Vector3::Zero);

	Camera::GetInstance().Update();

}

void OverLookingCamera::onDraw() const
{
}

void OverLookingCamera::onCollide(Actor & other)
{
}

void OverLookingCamera::cameraMove(float deltaTime)
{
}
