#include "OverLookingCamera.h"
#include"Camera.h"
#include"../Graphic/Model.h"
#include"../Actor/Dummy/BetweenPositionActor.h"
#include"../Input/Keyboard.h"
#include"../Math/Easing.h"

static const float defUpLength = 100.0f;
static const float defBackLength = 100.0f;
static const float zoomUpLength = 30.0f;
static const float zoomBackLength = 70.0f;

float zoomSpeed = 3.0f;

static const Vector3 defTargetVector{ 0.0f,-30.0f,-20.0f };
static const Vector3 zoomTargetVector{ 0.0f,0.0f,0.0f };

//�J�����̎��R�␳
static const Vector3 moveVector{ 0.0f,0.0f,0.0f };

OverLookingCamera::OverLookingCamera(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Actor(world, name, position, body), target_(nullptr), targetTranslate_(Vector3::Zero)
{
	zoomFuncList_.emplace_back([&](float deltaTime) {zoom_default(deltaTime); });
	zoomFuncList_.emplace_back([&](float deltaTime) {zoom_in(deltaTime); });
	zoomFuncList_.emplace_back([&](float deltaTime) {zoom_out(deltaTime); });

	backwardLength_ = defBackLength;
	upLength_ = defUpLength;
	targetVector_ = defTargetVector;

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
	zoomFuncList_[zoomType_](deltaTime);

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
		nextPos.y = upLength_+ addDistance;

		//�J�������g�̈ʒu�́A�Ώۂ̈ʒu����J��������萔�������ʒu�ɒu��
		position_ = Vector3::Lerp(nextPos, prevPosition_, 0.9f);
		prevPosition_ = nextPos;
		//�^�[�Q�b�g�̈ʒu��Ώۂ̈ʒu�ɐݒ�
		targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength_);
		targetPos.y = 0.0f;
		//�ꉞy���Œ肵����
		position_.y = upLength_ + addDistance;
		//z���Œ�l��������
		position_.z -= backwardLength_;


		////�J�������g�̈ʒu�́A�Ώۂ̈ʒu����J��������萔�������ʒu�ɒu��
		//position_ = Vector3::Lerp(nextPos, position_, 0.9f);
		////�^�[�Q�b�g�̈ʒu��Ώۂ̈ʒu�ɐݒ�ݒ�
		//targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength*10.0f);
		//targetPos.y = 0.0f;
		////�ꉞy���Œ肵����
		//position_.y = upLength+ addDistance;
		////z���Œ�l��������
		//position_.z -= backwardLength;
	}



	Camera::GetInstance().Position.Set(position_+moveVector);

	Camera::GetInstance().Target.Set(targetPos + targetVector_);
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

void OverLookingCamera::ZoomIn()
{
	zoomType_ = 1;
}

void OverLookingCamera::ZoomOut()
{
	zoomType_ = 2;
}

void OverLookingCamera::setFirstPos()
{
	Vector3 nextPos = target_->position();

	//�J������ǉ��ň�����
	float addDistance = 0.0f;
	//y���Œ肷��
	nextPos.y = upLength_ + addDistance;

	position_ = nextPos;
	prevPosition_ = nextPos;

	Vector3 targetPos = Vector3::Zero;
	targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength_);
	targetPos.y = 0.0f;
	//�ꉞy���Œ肵����
	position_.y = upLength_ + addDistance;
	//z���Œ�l��������
	position_.z -= backwardLength_;

	Camera::GetInstance().Position.Set(position_ + moveVector);

	Camera::GetInstance().Target.Set(targetPos + targetVector_);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(rotation_.Up());

	Camera::GetInstance().Update();

}

void OverLookingCamera::cameraMove(float deltaTime)
{
}

void OverLookingCamera::zoom_default(float deltaTime)
{
	
}

void OverLookingCamera::zoom_in(float deltaTime)
{
	timeCount_ += deltaTime*zoomSpeed;

	backwardLength_ = Easing::EaseInCubic(timeCount_, defBackLength, zoomBackLength - defBackLength, 1.0f);
	upLength_ = Easing::EaseOutCubic(timeCount_, defUpLength, zoomUpLength - defUpLength, 1.0f);
	targetVector_ = Easing::EaseOutCubic(timeCount_, defTargetVector, zoomTargetVector - defTargetVector, 1.0f);

	if (timeCount_ >= 1.0f) {
		zoomType_ = 0;
	}
}

void OverLookingCamera::zoom_out(float deltaTime)
{
	timeCount_ -= deltaTime*zoomSpeed;

	backwardLength_ = Easing::EaseInCubic(timeCount_, defBackLength, zoomBackLength - defBackLength, 1.0f);
	upLength_ = Easing::EaseOutCubic(timeCount_, defUpLength, zoomUpLength - defUpLength, 1.0f);
	targetVector_ = Easing::EaseOutCubic(timeCount_, defTargetVector, zoomTargetVector - defTargetVector, 1.0f);

	if (timeCount_ <= 0.0f) {
		zoomType_ = 0;
	}
}
