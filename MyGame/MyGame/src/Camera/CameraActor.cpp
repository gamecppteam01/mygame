#include "CameraActor.h"
#include"Camera.h"
#include"../Graphic/Model.h"
#include"../Input/InputChecker.h"

//�Ώۂ����둤�ɗ���鋗��
static const float backwardLength = 50.0f;
//�Ώۂ���㑤�ɗ���鋗��
static const float upLength = 20.0f;


CameraActor::CameraActor(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Actor(world,name,position,body),target_(nullptr), targetTranslate_(Vector3::Zero)
{
}

void CameraActor::setTarget(ActorPtr & target)
{
	target_ = target;
}

void CameraActor::onMessage(EventMessage message, void * param)
{
}

void CameraActor::onUpdate(float deltaTime)
{
	Vector3 targetPos = Vector3::Zero;
	if (target_ != nullptr) {
		//��U�Ώۂ̈ʒu�����ɂ���
		targetPos = target_->position();
		//�J�������g�̈ʒu�́A�Ώۂ̈ʒu����J��������萔�������ʒu�ɒu��

		position_ = Vector3::Lerp(targetPos+(target_->getPose().Backward()*backwardLength + target_->getPose().Up()*upLength),position_,0.9f);
		position_.y = (targetPos + (target_->getPose().Backward()*backwardLength + target_->getPose().Up()*upLength)).y;
		//position_ = targetPos + (target_->getPose().Backward()*backwardLength + target_->getPose().Up()*upLength);
		targetPos += target_->getPose().Up()*10.0f;
		targetPos += targetTranslate_;
	}

	Camera::GetInstance().Position.Set(position_);

	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(rotation_.Up());
	//Camera::GetInstance().SetRotation(Vector3::Zero);

	Camera::GetInstance().Update();

}

void CameraActor::onDraw() const
{
}

void CameraActor::onCollide(Actor & other)
{
}

void CameraActor::cameraMove(float deltaTime)
{
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Right)) {
		targetTranslate_ += Vector3(0.0f, 0.0f, 0.0f);
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Left)) {
		targetTranslate_ += Vector3(0.0f, 0.0f, 0.0f);
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Up)) {
		targetTranslate_ += Vector3(0.0f, 0.0f, 0.0f);
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Down)) {
		targetTranslate_ += Vector3(0.0f, 0.0f, 0.0f);
	}

}
