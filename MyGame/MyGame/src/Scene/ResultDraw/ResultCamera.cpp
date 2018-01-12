#include "ResultCamera.h"
#include"../../Camera/Camera.h"
#include"../../Math/Easing.h"
#include<functional>
#include<map>

static const Vector3 forwardVector{ 0.0f,-20.0f,30.0f };
static const Vector3 defaultCameraPos{ 0.0f,50.0f,-40.0f };
static const std::map<ResultEasingType, std::function<float(float, float, float, float)>> easeList_{
	{ ResultEasingType::Linear,[](float t,float b,float c,float d) {return Easing::Linear(t,b,c,d); } },
	{ ResultEasingType::EaseOutQuad,[](float t,float b,float c,float d) {return Easing::EaseOutQuad(t,b,c,d); } },
	{ ResultEasingType::EaseInCirc,[](float t,float b,float c,float d) {return Easing::EaseInCirc(t,b,c,d); } },
};

ResultCamera::ResultCamera()
{
}

void ResultCamera::init()
{
	target_ = defaultCameraPos;
	nextTarget_ = defaultCameraPos;
	lerpTimer_ = 0.0f;
	xEase_ = ResultEasingType::Linear;
	yEase_ = ResultEasingType::Linear;
	zEase_ = ResultEasingType::Linear;

}

void ResultCamera::start(const Vector3 & nextTarget, const Vector3& add, ResultEasingType xEase, ResultEasingType yEase, ResultEasingType zEase)
{
	Vector3 current = currentTarget();

	Vector3 targetAddVec{ Vector3::Zero };
	targetAddVec.x = easeList_.at(xEase_)(lerpTimer_, targetAddVector_.x, nextTargetAddVector_.x - targetAddVector_.x, 1.0f);
	targetAddVec.y = easeList_.at(yEase_)(lerpTimer_, targetAddVector_.y, nextTargetAddVector_.y - targetAddVector_.y, 1.0f);
	targetAddVec.z = easeList_.at(zEase_)(lerpTimer_, targetAddVector_.z, nextTargetAddVector_.z - targetAddVector_.z, 1.0f);

	targetAddVector_ = targetAddVec;
	nextTargetAddVector_ = add;

	target_ = current;
	nextTarget_ = nextTarget;
	lerpTimer_ = 0.0f;
	xEase_ = xEase;
	yEase_ = yEase;
	zEase_ = zEase;
}

void ResultCamera::update(float deltaTime)
{
	lerpTimer_ = min(lerpTimer_ + deltaTime, 1.0f);
}

void ResultCamera::draw() const
{
	float up = 50.0f;
	float back = -100.0f;
	Vector3 current = currentTarget();
	Camera::GetInstance().Position.Set(current + Vector3{ 0.0f,up,back });
	
	Vector3 targetAddVec{ Vector3::Zero };
	targetAddVec.x = easeList_.at(xEase_)(lerpTimer_, targetAddVector_.x, nextTargetAddVector_.x - targetAddVector_.x, 1.0f);
	targetAddVec.y = easeList_.at(yEase_)(lerpTimer_, targetAddVector_.y, nextTargetAddVector_.y - targetAddVector_.y, 1.0f);
	targetAddVec.z = easeList_.at(zEase_)(lerpTimer_, targetAddVector_.z, nextTargetAddVector_.z - targetAddVector_.z, 1.0f);

	Camera::GetInstance().Target.Set(current + Vector3{ 0.0f,up+ targetAddVec.y,0.0f });
	Camera::GetInstance().SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);

	Camera::GetInstance().Update();

}

void ResultCamera::zoomIn()
{
	target_ = currentTarget();
	nextTarget_ = target_ + forwardVector;
	lerpTimer_ = 0.0f;
}

void ResultCamera::zoomOut()
{
	target_ = currentTarget();
	nextTarget_ = target_ - forwardVector;
	lerpTimer_ = 0.0f;
}

bool ResultCamera::isEnd() const
{
	return lerpTimer_ >= 1.0f;
}

Vector3 ResultCamera::currentTarget() const
{
	Vector3 result{ Vector3::Zero };
	result.x = easeList_.at(xEase_)(lerpTimer_, target_.x, nextTarget_.x - target_.x, 1.0f);
	result.y = easeList_.at(yEase_)(lerpTimer_, target_.y, nextTarget_.y - target_.y, 1.0f);
	result.z = easeList_.at(zEase_)(lerpTimer_, target_.z, nextTarget_.z - target_.z, 1.0f);

	return result;
}

