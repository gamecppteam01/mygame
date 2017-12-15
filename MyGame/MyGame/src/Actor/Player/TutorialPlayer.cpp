#include "TutorialPlayer.h"
#include"../../Scene/TutorialScene.h"
#include"../../Input/InputChecker.h"
#include"../../Math/Random.h"

//‘«‚ğ~‚ß‚éƒŒƒbƒXƒ“”Ô†
static const std::list<int> stopList{
	2,
	3
};

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
	if (tutorial_->getTutorialNum() == 1&&hitCount_ >= 3) {
		checkstep_.initialize();
		checkstep_.setInputLimit(std::list<Player_Animation>{Player_Animation::Shoot, Player_Animation::Half, Player_Animation::Turn});
		checkstep_.setInputRelease(std::list<Player_Animation>{Player_Animation::Quarter});
		tutorial_->nextLesson();
	}
}

void TutorialPlayer::textEnd(int lessonNum)
{
	if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) != stopList.end()) {//”Ô†‚É‰‚¶‚Ä“ü—Í‚ğ§ŒÀ‚·‚é	
		if (state_ != Player_State::Move)return;
		change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward);
	}
}

bool TutorialPlayer::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop, float blend)
{
	if (state == Player_State::Stumble)return false;
	return Player::change_State_and_Anim(state, animID, animFrame, animSpeed, isLoop, blend);
}
void TutorialPlayer::idle_Update(float deltaTime)
{
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) > ignoreSlope || std::abs(move.y) > ignoreSlope) {
		if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) == stopList.end()) {//”Ô†‚É‰‚¶‚Ä“ü—Í‚ğ§ŒÀ‚·‚é	
			/*if (*/change_State_and_Anim(Player_State::Move, Player_Animation::Move_Forward);//)playerUpdateFunc_[state_](deltaTime);
			return;
		}
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot, 0.0f, 1.0f, false))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (isChangeStep()) {
		if (isJustTiming()) {
			change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left);//)playerUpdateFunc_[state_](deltaTime);
		}
		else {
			std::vector<Vector2> stumbleList{
				Vector2::Right,
				Vector2::Left,
				Vector2::Up,
				Vector2::Down
			};
			stumbleDirection_ = stumbleList[Random::GetInstance().Range(0, 3)];

			change_State_and_Anim(Player_State::Stumble, Player_Animation::Stumble);//)playerUpdateFunc_[state_](deltaTime);

		}
		return;
	}
	upVelocity_ -= upVelocity_*0.5f;

	gravityUpdate(deltaTime);

}

void TutorialPlayer::to_MoveMode()
{
	if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) != stopList.end()) {//”Ô†‚É‰‚¶‚Ä“ü—Í‚ğ§ŒÀ‚·‚é	
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
		if (tutorial_->getTutorialNum() == 2) {
			tutorial_->nextLesson();
			checkstep_.initialize();
			checkstep_.setInputLimit(std::list<Player_Animation>{Player_Animation::Shoot, Player_Animation::Half, Player_Animation::Quarter});
			checkstep_.setInputRelease(std::list<Player_Animation>{Player_Animation::Turn});
			break;
		}
	case 2:
		break;
	case 3:
		if (tutorial_->getTutorialNum() == 3) {
			tutorial_->nextLesson();
		}
		break;
	case 4:
		break;
	default:
		break;
	}
}

