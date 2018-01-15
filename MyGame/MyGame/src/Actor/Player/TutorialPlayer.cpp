#include "TutorialPlayer.h"
#include"../../Scene/TutorialScene.h"
#include"../../Input/InputChecker.h"
#include"../../Math/Random.h"
#include"../Judge/Judgement_SpotLight/Judgement_SpotLight.h"

//足を止めるレッスン番号
static const std::list<int> stopList{
	5,
	7,
	9,
	11
};

TutorialPlayer::TutorialPlayer(IWorld * world, const std::string & name, const Vector3 & position, TutorialScene * tutorial):
	Player(world,name,position,1),tutorial_(tutorial), hitCount_(0), isAlreadyInLight_(false)
{
}

void TutorialPlayer::onUpdate(float deltaTime)
{
	Player::onUpdate(deltaTime);

	switch (tutorial_->getTutorialNum())
	{
	//スポットライトのチュートリアル
	case 13: {
		auto ptr = std::dynamic_pointer_cast<Judgement_SpotLight>(world_->findActor("SpotLight"));
		if (ptr != nullptr) {
			//既にライトに当たってたら当たらなくなったかを検索
			if (isAlreadyInLight_) {
				//ライトから外れたら次へ(カメラの関係上ステップ系中は戻らない)
				if (!ptr->getIsNotice(playerNumber_)&&
					state_ != Player_State::Step&&
					state_ != Player_State::Step_Success&&
					state_ != Player_State::Attack&&
					state_ != Player_State::Shoot&&
					state_ != Player_State::ShootEnd
					)tutorial_->nextLesson();
				return;
			}
			//当たってるか検索
			if (ptr->getIsNotice(playerNumber_)) {
				isAlreadyInLight_ = true;
			}
		}
		break;
	}
	case 14: {
		if (checkstep_.isEndCheck()) {
			tutorial_->nextLesson();
		}
		break;
	}
	case 15: {
		if (comboType_ == ComboChecker::ComboType::Combo_PointUp)tutorial_->nextLesson();
		break;
	}
	case 16: {
		if (comboType_ == ComboChecker::ComboType::Combo_Burst)tutorial_->nextLesson();
		break;
	}
	default:
		break;
	}
}


void TutorialPlayer::hitPoint()
{
	hitCount_++;
	if (tutorial_->getTutorialNum() == 3&&hitCount_ >= 3) {
		tutorial_->nextLesson();
	}
}

void TutorialPlayer::textEnd(int lessonNum)
{
	if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) != stopList.end()) {//番号に応じて入力を制限する	
		if (state_ != Player_State::Move)return;
		change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward);
	}
}

void TutorialPlayer::resetCombo()
{
	comboChecker_.clear();
	comboType_ = ComboChecker::ComboType::Combo_None;
	isChangeBurstMode_ = false;
	auto stepdrawer = world_->findUI("ComboDrawer");
	if (stepdrawer != nullptr)stepdrawer->Notify(Notification::Call_Combo_Reset);

}

bool TutorialPlayer::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop, float blend)
{
	switch (tutorial_->getTutorialNum())
	{
	case 3: {
		if (state == Player_State::Step)return false;
		break;
	}
	default:
		break;
	}
	if (
		tutorial_->getTutorialNum() != 13 &&
		tutorial_->getTutorialNum() != 14 &&
		tutorial_->getTutorialNum() != 15 &&
		tutorial_->getTutorialNum() != 16
		) {
		if (state == Player_State::Stumble)return false;
	}
	return Player::change_State_and_Anim(state, animID, animFrame, animSpeed, isLoop, blend);
}
void TutorialPlayer::idle_Update(float deltaTime)
{
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) > ignoreSlope || std::abs(move.y) > ignoreSlope) {
		if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) == stopList.end()) {//番号に応じて入力を制限する	
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

			//成功通知
			auto stepUI = world_->findUI("StepUI");
			if (stepUI != nullptr)stepUI->Notify(Notification::Call_StepFailed);
			change_State_and_Anim(Player_State::Stumble, Player_Animation::Stumble);//)playerUpdateFunc_[state_](deltaTime);

		}
		return;
	}
	upVelocity_ -= upVelocity_*0.5f;

	gravityUpdate(deltaTime);

}

void TutorialPlayer::to_MoveMode()
{
	if (std::find(stopList.begin(), stopList.end(), tutorial_->getTutorialNum()) != stopList.end()) {//番号に応じて入力を制限する	
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
		if (tutorial_->getTutorialNum() == 5) {
			tutorial_->nextLesson();
			break;
		}
	case 2:
		break;
	case 3:
		if (tutorial_->getTutorialNum() == 7) {
			tutorial_->nextLesson();
		}
		break;
	case 4:
		break;
	default:
		break;
	}
}

void TutorialPlayer::end_AttackMode()
{
	Player::end_AttackMode();

	if (tutorial_->getTutorialNum() == 9) {
		tutorial_->nextLesson();
	}

}

void TutorialPlayer::end_ShootMode()
{
	Player::end_ShootMode();

	if (tutorial_->getTutorialNum() == 11) {
		tutorial_->nextLesson();
	}

}

