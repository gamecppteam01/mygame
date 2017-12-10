#include "TutorialPlayer.h"
#include"../../Scene/TutorialScene.h"
#include"../../Input/InputChecker.h"
#include"../../Math/Random.h"

TutorialPlayer::TutorialPlayer(IWorld * world, const std::string & name, const Vector3 & position, TutorialScene * tutorial):
	Player(world,name,position,1),tutorial_(tutorial), hitCount_(0)
{
}

TutorialPlayer::~TutorialPlayer()
{
}

void TutorialPlayer::onUpdate(float deltaTime)
{
	Player::onUpdate(deltaTime);
}


void TutorialPlayer::hitPoint()
{
	hitCount_++;
	if (hitCount_ >= 3)tutorial_->nextLesson();
}

bool TutorialPlayer::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop, float blend)
{
	if (state == Player_State::Stumble)return false;
	return Player::change_State_and_Anim(state, animID, animFrame, animSpeed, isLoop, blend);
}

void TutorialPlayer::to_MoveMode()
{
	std::list<int> stopList{
		2,
		3
	};
	if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) != stopList.end()) {//”Ô†‚É‰ž‚¶‚Ä“ü—Í‚ð§ŒÀ‚·‚é	
		change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward);
	}
	else {
		Player::to_MoveMode();
	}
}

void TutorialPlayer::end_StepSuccessMode()
{
	Player::end_StepSuccessMode();
	switch (nextStep_)
	{
	case 1:
		if (tutorial_->getTutorialNum() == 2)tutorial_->nextLesson();
		break;
	case 2:
		break;
	case 3:
		if (tutorial_->getTutorialNum() == 3)tutorial_->nextLesson();
		break;
	case 4:
		break;
	default:
		break;
	}
}

