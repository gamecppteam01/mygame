#include "OverLookingCamera.h"
#include"Camera.h"
#include"../Graphic/Model.h"
#include"../Actor/Dummy/BetweenPositionActor.h"

//対象から後ろ側に離れる距離
static const float backwardLength = 3.0f;
//対象から上側に離れる距離
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
		//一旦対象の位置を軸にする
		Vector3 nextPos= target_->position();

		//カメラを追加で引く量
		float addDistance = 0.0f;
		if (target_->getName() == "Point") {
			addDistance = std::static_pointer_cast<BetweenPositionActor>(target_)->getDistance()*0.5f;
		}
		//yを固定する
		nextPos.y = upLength+ addDistance;

		//カメラ自身の位置は、対象の位置からカメラを特定数離した位置に置く
		position_ = Vector3::Lerp(nextPos, position_, 0.9f);
		//ターゲットの位置を対象の位置に設定設定
		targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength*10.0f);
		targetPos.y = 0.0f;
		//一応yを固定し直す
		position_.y = upLength+ addDistance;
		//zを固定値分下げる
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
