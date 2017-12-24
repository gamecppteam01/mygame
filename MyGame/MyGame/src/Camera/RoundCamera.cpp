#include "RoundCamera.h"
#include"../World/IWorld.h"
#include"../Actor/Actor.h"
#include"Camera.h"
#include"../Math/Easing.h"

RoundCamera::RoundCamera(IWorld* world):world_(world), isEnd_(true)
{
}

void RoundCamera::init()
{
	targetList_.clear();

	auto player = world_->findActor("Player");
	std::list<ActorPtr> enemy;
	world_->findActors("Enemy", enemy);

	targetList_.push_back(player);
	std::copy(enemy.begin(), enemy.end(), std::back_inserter(targetList_));

	currentTarget_ = 0;
	moveTimer_ = 0.0f;
	state_ = State::Move;

	position_ = Camera::GetInstance().Position.Get();
	//position_ = targetList_.front().lock()->position();
	defaultPos_ = Camera::GetInstance().Position.Get();
	startPosition_ = position_;
	targetVector_ = Camera::GetInstance().Target.Get() - defaultPos_;
	isEnd_ = false;
}

void RoundCamera::onUpdate(float deltaTime)
{
	switch (state_)
	{
	case RoundCamera::State::Focus:
		Focus(deltaTime);
		break;
	case RoundCamera::State::Move:
		Move(deltaTime);
		break;
	case RoundCamera::State::Return:
		Return(deltaTime);
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

void RoundCamera::Focus(float deltaTime)
{
	moveTimer_ += deltaTime;
	if (moveTimer_ >= 1.0f)changeState(State::Move);
}

void RoundCamera::Move(float deltaTime)
{
	moveTimer_ += deltaTime;

	position_ = Easing::EaseOutQuad(moveTimer_, startPosition_, targetList_.at(currentTarget_).lock()->position() + outVector_ - startPosition_, 1.0f);

	if (moveTimer_ >= 1.0f)changeState(State::Focus);
}

void RoundCamera::Return(float deltaTime)
{
	if (isEnd_)return;

	moveTimer_ += deltaTime;

	position_ = Easing::EaseOutQuad(moveTimer_, startPosition_, defaultPos_ - startPosition_, 1.0f);

	if (moveTimer_ >= 1.0f) {
		moveTimer_ = 1.0f;
		isEnd_ = true;
	}
}

void RoundCamera::changeState(State state)
{
	switch (state_)
	{
	case RoundCamera::State::Focus:
		currentTarget_++;
		if (currentTarget_ >= targetList_.size())state = State::Return;
		break;
	case RoundCamera::State::Move:
		break;
	case RoundCamera::State::Return:
		break;
	default:
		break;
	}
	state_ = state;

	switch (state_)
	{
	case RoundCamera::State::Focus:
		moveTimer_ = 0.0f;
		break;
	case RoundCamera::State::Move:
		moveTimer_ = 0.0f;
		startPosition_ = position_;
		break;
	case RoundCamera::State::Return:
		moveTimer_ = 0.0f;
		startPosition_ = position_;
		break;
	default:
		break;
	}
}
