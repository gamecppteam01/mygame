#include "SpecifiedStepUI.h"

SpecifiedStepUI::SpecifiedStepUI(IWorld * world)
	: UI{ "SpecifiedStepUI", position_ }, world_(world)
{
	initialize();
}

void SpecifiedStepUI::initialize()
{
	reciveList_.clear();
	pause_ = false;
	Ypos = 520.0f; Xpos = 1280.0f; count_ = 0;
	cursorPos_ = Vector2(110.0f, 520.0f);
	stepState_ = StepState::NONE;
	state_ = State::Two;
	stepMap_.clear();
	//マップに格納
	stepMap_[ReciveStep_] = SPRITE_ID::QUATER_SPRITE;
	stepMap_[ReciveStep_] = SPRITE_ID::HALF_SPRITE;
	stepMap_[ReciveStep_] = SPRITE_ID::TURN_SPRITE;
	stepMap_[ReciveStep_] = SPRITE_ID::SPIN_SPRITE;

	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	for (int i = 0; i < Directiv; i++) {
		reciveList_.push_back(ReciveStep_);
	}

}

void SpecifiedStepUI::update(float deltaTime)
{
	//指示ステップをしたら、その文字が光って下に落ちる（フェードしながら）、左詰めにする
	//指示ステップが成功したら一つ目の要素を消して、再描画する

	//指定のステップと合っていたら消して左詰め
	//ステップ １クオーター、２ハーフ、３ターン、４スピン
	if (stepState_ == stepMatching() && state_ == State::One)    reciveList_.erase(reciveList_.begin()), state_ = State::Two  ,    alpha_ = 0.0f ;
	if (stepState_ == stepMatching() && state_ == State::One)    reciveList_.erase(reciveList_.begin()), state_ = State::Two  ,    alpha_ = 0.0f ;
	if (stepState_ == stepMatching() && state_ == State::One)    reciveList_.erase(reciveList_.begin()), state_ = State::Two  ,    alpha_ = 0.0f ;
	if (stepState_ == stepMatching() && state_ == State::One)    reciveList_.erase(reciveList_.begin()), state_ = State::Two  ,    alpha_ = 0.0f ;
															   																  				   
	if (stepState_ == stepMatching() && state_ == State::Two)    reciveList_.erase(reciveList_.begin()), state_ = State::Three,    alpha2_ = 0.0f;
	if (stepState_ == stepMatching() && state_ == State::Two)    reciveList_.erase(reciveList_.begin()), state_ = State::Three,    alpha2_ = 0.0f;
	if (stepState_ == stepMatching() && state_ == State::Two)    reciveList_.erase(reciveList_.begin()), state_ = State::Three,    alpha2_ = 0.0f;
	if (stepState_ == stepMatching() && state_ == State::Two)    reciveList_.erase(reciveList_.begin()), state_ = State::Three,    alpha2_ = 0.0f;
																															  				   
	if (stepState_ == stepMatching() && state_ == State::Three)  reciveList_.erase(reciveList_.begin()), state_ = State::Four ,    alpha3_ = 0.0f;
	if (stepState_ == stepMatching() && state_ == State::Three)  reciveList_.erase(reciveList_.begin()), state_ = State::Four ,    alpha3_ = 0.0f;
	if (stepState_ == stepMatching() && state_ == State::Three)  reciveList_.erase(reciveList_.begin()), state_ = State::Four ,    alpha3_ = 0.0f;
	if (stepState_ == stepMatching() && state_ == State::Three)  reciveList_.erase(reciveList_.begin()), state_ = State::Four ,    alpha3_ = 0.0f;

	if (stepState_ == stepMatching() && state_ == State::Four)   reciveList_.erase(reciveList_.begin())/*, state_ = State::Two,  alpha4_ = 0.0f*/;
	if (stepState_ == stepMatching() && state_ == State::Four)   reciveList_.erase(reciveList_.begin())/*, state_ = State::Two,  alpha4_ = 0.0f*/;
	if (stepState_ == stepMatching() && state_ == State::Four)   reciveList_.erase(reciveList_.begin())/*, state_ = State::Two,  alpha4_ = 0.0f*/;
	if (stepState_ == stepMatching() && state_ == State::Four)   reciveList_.erase(reciveList_.begin())/*, state_ = State::Two,  alpha4_ = 0.0f*/;


	//ラープ用タイマー
	if (lerpTimer_ <= 1.0f) lerpTimer_ += 0.1f;

	//alpha_ = MathHelper::Lerp(1.0f, 0.0f, lerpTimer_);
	Xpos = MathHelper::Lerp(1280.0f, 120.0f, lerpTimer_);
}

void SpecifiedStepUI::draw() const
{
	if (state_ == State::One) {
	for (int i = 0; i < reciveList_.size(); i++) {

		Sprite::GetInstance().Draw(stepMap_.at(ReciveStep_), Vector2(Xpos, Ypos) + Vector2(120.0f, 0.0f) * i, alpha_);
	}
	}
	if (state_ == State::Two) {
		for (int i = 0; i < reciveList_.size(); i++) {

			Sprite::GetInstance().Draw(stepMap_.at(ReciveStep_), Vector2(Xpos, Ypos) + Vector2(120.0f, 0.0f) * i, alpha2_);
		}
	}
	if(state_ == State::Three){
		for (int i = 0; i < reciveList_.size(); i++) {

			Sprite::GetInstance().Draw(stepMap_.at(ReciveStep_), Vector2(Xpos, Ypos) + Vector2(120.0f, 0.0f) * i, alpha3_);
		}
	}
	if (state_ == State::Four) {
		for (int i = 0; i < reciveList_.size(); i++) {

			Sprite::GetInstance().Draw(stepMap_.at(ReciveStep_), Vector2(Xpos, Ypos) + Vector2(120.0f, 0.0f) * i, alpha4_);
		}
	}

	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_CURSOR, cursorPos_, 1.0f);
}

void SpecifiedStepUI::pause()
{
	pause_ = true;
}

void SpecifiedStepUI::restart()
{
	pause_ = false;
}

//パラメータに値が飛んでくる
void SpecifiedStepUI::Notify(Notification type, void * param)
{
	if (type == Notification::Call_ReciveStep) {
		ReciveStep_ = *(int*)param;
	}

}

//ステップが合っているかを調べ結果を返す
int SpecifiedStepUI::stepMatching() {
	if (target_->getStep() == 1 && target_->getState() == Player::Player_State::Step_Success) {
		return StepState::QUARTER;
	}
	if (target_->getStep() == 2 && target_->getState() == Player::Player_State::Attack) {
		return StepState::HALF;
	}
	if (target_->getStep() == 3 && target_->getState() == Player::Player_State::Step_Success) {
		return StepState::TURN;
	}
	//ここが謎
	if (target_->getStep() == 4 && target_->getState() == Player::Player_State::Shoot) {
		return StepState::SPIN;
	}
	if (target_->getStep() == 0) {
		return StepState::NONE;
	}
}
