#include "OverLookingCamera.h"
#include"Camera.h"
#include"../Graphic/Model.h"
#include"../Actor/Dummy/BetweenPositionActor.h"
#include"../Input/Keyboard.h"
#include"../Math/Easing.h"

static const float defUpLength=100.0f;
static const float defBackLength=100.0f;
static const std::vector<float> zoomUpLength{
	30.0f,
	80.0f
};
static const std::vector<float> zoomBackLength{
	80.0f,
	80.0f
};

static const float zoomSpeed = 3.0f;

static const Vector3 defTargetVector{ 0.0f,-30.0f,-20.0f };
static const std::vector<Vector3> zoomTargetVector{
	{ 0.0f,0.0f,0.0f },
	{ 0.0f,-30.0f,-20.0f }
};

//カメラの自由補正
static const Vector3 moveVector{ 0.0f,0.0f,0.0f };

OverLookingCamera::OverLookingCamera(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Actor(world, name, position, body), target_(nullptr), targetTranslate_(Vector3::Zero)
{
	zoomFuncList_.emplace_back([&](float deltaTime) {zoom_default(deltaTime); });
	zoomFuncList_.emplace_back([&](float deltaTime) {zoom_in(deltaTime); });
	zoomFuncList_.emplace_back([&](float deltaTime) {zoom_out(deltaTime); });

	//通常ステップ用のカメラ移動
	easeFuncList_.emplace_back([&]() {
		backwardLength_ = Easing::EaseInCubic(timeCount_, defBackLength, zoomBackLength[pointKey_] - defBackLength, 1.0f);
		upLength_ = Easing::EaseOutCubic(timeCount_, defUpLength, zoomUpLength[pointKey_] - defUpLength, 1.0f);
		targetVector_ = Easing::EaseOutCubic(timeCount_, defTargetVector, zoomTargetVector[pointKey_] - defTargetVector, 1.0f);
	});
	//直線移動用のカメラ移動
	easeFuncList_.emplace_back([&]() {
		backwardLength_ = Easing::EaseOutCubic(timeCount_, defBackLength, zoomBackLength[pointKey_] - defBackLength, 1.0f);
		upLength_ = Easing::EaseOutCubic(timeCount_, defUpLength, zoomUpLength[pointKey_] - defUpLength, 1.0f);
		//targetVector_ = Easing::EaseOutCubic(timeCount_, defTargetVector, zoomTargetVector[pointKey_] - defTargetVector, 1.0f);
	});

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
		//一旦対象の位置を軸にする
		Vector3 nextPos= target_->position();

		//カメラを追加で引く量
		float addDistance = 0.0f;
		if (target_->getName() == "Point") {
			addDistance = std::static_pointer_cast<BetweenPositionActor>(target_)->getDistance()*0.5f;
		}
		//yを固定する
		nextPos.y = upLength_+ addDistance;

		//カメラ自身の位置は、対象の位置からカメラを特定数離した位置に置く
		position_ = Vector3::Lerp(nextPos, prevPosition_, 0.9f);
		prevPosition_ = nextPos;
		//ターゲットの位置を対象の位置に設定
		targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength_);
		targetPos.y = 0.0f;
		//一応yを固定し直す
		position_.y = upLength_ + addDistance;
		//zを固定値分下げる
		position_.z -= backwardLength_;


		////カメラ自身の位置は、対象の位置からカメラを特定数離した位置に置く
		//position_ = Vector3::Lerp(nextPos, position_, 0.9f);
		////ターゲットの位置を対象の位置に設定設定
		//targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength*10.0f);
		//targetPos.y = 0.0f;
		////一応yを固定し直す
		//position_.y = upLength+ addDistance;
		////zを固定値分下げる
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

void OverLookingCamera::ZoomIn(int pointKey, int easeKey)
{
	zoomType_ = 1;
	pointKey_ = pointKey;
	easeKey_ = easeKey;
}

void OverLookingCamera::ZoomOut()
{
	zoomType_ = 2;
}

void OverLookingCamera::setFirstPos()
{
	Vector3 nextPos = target_->position();

	//カメラを追加で引く量
	float addDistance = 0.0f;
	//yを固定する
	nextPos.y = upLength_ + addDistance;

	position_ = nextPos;
	prevPosition_ = nextPos;

	Vector3 targetPos = Vector3::Zero;
	targetPos = position_ + Vector3(0.0f, 0.0f, backwardLength_);
	targetPos.y = 0.0f;
	//一応yを固定し直す
	position_.y = upLength_ + addDistance;
	//zを固定値分下げる
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
	if (timeCount_ >= 1.0f) {
		timeCount_ = 1.0f;
		zoomType_ = 0;
	}

	easeFuncList_[easeKey_]();

}

void OverLookingCamera::zoom_out(float deltaTime)
{
	timeCount_ -= deltaTime*zoomSpeed;
	if (timeCount_ <= 0.0f) {
		timeCount_ = 0.0f;
		zoomType_ = 0;
	}

	easeFuncList_[easeKey_]();

}
