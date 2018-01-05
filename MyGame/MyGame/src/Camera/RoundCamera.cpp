#include "RoundCamera.h"
#include"../World/IWorld.h"
#include"../Actor/Actor.h"
#include"Camera.h"
#include"../Math/Easing.h"
#include"../Scene/Screen/TutorialCutIn.h"
#include"../Sound/Sound.h"

RoundCamera::RoundCamera(IWorld* world):world_(world), isEnd_(true)
{
}

void RoundCamera::init()
{
	targetList_.clear();
	func_ = [] {};

	auto player = world_->findActor("Player");
	std::list<ActorPtr> enemy;
	world_->findActors("Enemy", enemy);

	targetList_.push_back(player);
	std::copy(enemy.begin(), enemy.end(), std::back_inserter(targetList_));

	currentTarget_ = 0;
	moveTimer_ = 0.0f;
	state_ = State::Start;

	position_ = Camera::GetInstance().Position.Get();
	//position_ = targetList_.front().lock()->position();
	defaultPos_ = Camera::GetInstance().Position.Get();
	startPosition_ = position_;
	targetVector_ = Camera::GetInstance().Target.Get() - defaultPos_;

	firstPos_ = targetList_.front().lock()->position() + outVector_;
	isEnd_ = false;
	cutInTime_ = 0.0f;
	cheerVolume_ = 0.0f;
}

void RoundCamera::onUpdate(float deltaTime)
{
	switch (state_)
	{
	case RoundCamera::State::Start:
		Start(deltaTime);
		break;
	case RoundCamera::State::Focus:
		Focus(deltaTime);
		break;
	case RoundCamera::State::Move:
		Move(deltaTime);
		break;
	case RoundCamera::State::Return:
		Return(deltaTime);
		break;
	case RoundCamera::State::End:
		End(deltaTime);
		break;
	default:
		break;
	}

	Camera::GetInstance().Position.Set(position_);

	Camera::GetInstance().Target.Set(position_+targetVector_);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);
	//Camera::GetInstance().SetRotation(Vector3::Zero);

	Camera::GetInstance().Update();

}

void RoundCamera::onDraw() const
{
	if (currentTarget_ >= cutin_ids_.size())return;//”ÍˆÍŠO‚ÍƒŠƒ^[ƒ“
	if(state_==State::Focus)TutorialCutIn::draw(cutin_ids_.at(currentTarget_), 100.0f, cutInTime_, 1.0f, 0.5f, 0.5f);
}

Vector3 RoundCamera::getCurrentTargetPos() const { 
	if (currentTarget_ >= targetList_.size())return Vector3::Zero;
	return targetList_.at(currentTarget_).lock()->position(); 
}

void RoundCamera::Start(float deltaTime)
{
	moveTimer_ += deltaTime;
	if (moveTimer_ >= 0.5f)changeState(State::Move);
}

void RoundCamera::Focus(float deltaTime)
{
	cheerVolume_ += deltaTime;
	Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, cheerVolume_);
	cutInTime_ += deltaTime;
	targetList_.at(currentTarget_).lock()->stepAnimUpdate(deltaTime);

	if (targetList_.at(currentTarget_).lock()->isStepAnimEnd()) {
		func_ = [&] {moveTimer_ += deltaTime; };
		targetList_.at(currentTarget_).lock()->endStepAnim();
	}
	func_();
	if (moveTimer_ >= 0.5f) {
		changeState(State::Move);

	}
}

void RoundCamera::Move(float deltaTime)
{
	cheerVolume_ -= deltaTime*5.0f;
	Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, cheerVolume_);

	moveTimer_ += deltaTime;

	position_ = Easing::EaseOutQuad(moveTimer_, startPosition_, targetList_.at(currentTarget_).lock()->position() + outVector_ - startPosition_, 1.0f);

	if (moveTimer_ >= 1.0f)changeState(State::Focus);
}

void RoundCamera::Return(float deltaTime)
{
	cheerVolume_ -= deltaTime*5.0f;
	Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, cheerVolume_);

	//moveTimer_ += deltaTime;
	//
	//position_ = Easing::EaseOutQuad(min(1.0f, moveTimer_), startPosition_, firstPos_ - startPosition_, 1.0f);
	//
	//if (moveTimer_ >= 0.4f)changeState(State::End);

}

void RoundCamera::End(float deltaTime)
{
	if (isEnd_)return;

	moveTimer_ += deltaTime;

	//position_ = Easing::EaseOutQuad(moveTimer_, startPosition_, defaultPos_ - startPosition_, 1.0f);
	float time = 2.0f;
	position_.x = Easing::EaseOutCubic(min(time,moveTimer_), startPosition_.x, (defaultPos_ - startPosition_).x, time);
	position_.z = Easing::EaseOutCubic(min(time,moveTimer_), startPosition_.z, (defaultPos_ - startPosition_).z, time);
	position_.y = Easing::EaseOutQuad (min(time,moveTimer_), startPosition_.y, (defaultPos_ - startPosition_).y, time);

	if (moveTimer_ >= time + 0.2f) {
		moveTimer_ = time;
		isEnd_ = true;
	}

}

void RoundCamera::changeState(State state)
{
	switch (state_)
	{
	case RoundCamera::State::Start:
		break;
	case RoundCamera::State::Focus:
		currentTarget_++;
		func_ = [] {};
		if (currentTarget_ >= targetList_.size())state = State::Return;
		break;
	case RoundCamera::State::Move:
		break;
	case RoundCamera::State::Return:
		Sound::GetInstance().StopSE(SE_ID::CHEER_SE);

		break;
	case RoundCamera::State::End:
		break;

	default:
		break;
	}
	state_ = state;

	switch (state_)
	{
	case RoundCamera::State::Start:
		moveTimer_ = 0.0f;
		break;
	case RoundCamera::State::Focus:
		moveTimer_ = 0.0f;
		targetList_.at(currentTarget_).lock()->startStepAnim();
		cutInTime_ = 0.0f;
		Sound::GetInstance().PlaySE(SE_ID::CHEER_SE);
		cheerVolume_ = 0.0f;
		Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, cheerVolume_);
		break;
	case RoundCamera::State::Move:
		moveTimer_ = 0.0f;
		startPosition_ = position_;
		break;
	case RoundCamera::State::Return:
		changeState(State::End);
		moveTimer_ = 0.0f;
		startPosition_ = position_;
		break;
	case RoundCamera::State::End:
		moveTimer_ = 0.0f;
		startPosition_ = position_;
		break;
	default:
		break;
	}
}
