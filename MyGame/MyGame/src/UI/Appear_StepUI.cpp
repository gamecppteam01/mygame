#include"Appear_StepUI.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/DxlibGraphic.h"
#include"../Actor/Player/Player.h"

Appear_StepUI::Appear_StepUI(IWorld * world,Player* player):
	world_(world){
	player_ = player;
}

Appear_StepUI::~Appear_StepUI(){
}

void Appear_StepUI::SetWorld(IWorld * world){
	world_ = world;
}

void Appear_StepUI::Initialize(){
	stepDrawType_ = -1;
}

void Appear_StepUI::Update(float deltaTime){
}

void Appear_StepUI::Draw(const Vector3 & position) const{
	if (player_->getState() == Player::Player_State::Step) {
		if (stepDrawType_ == -1)return;

		DrawSprite3D(position, 12.5f, stepDrawType_);
	}
}

void Appear_StepUI::Notify(int stepType)
{
	switch (player_->getStep())
	{
	case 0:
		stepDrawType_ = -1;
		break;
	case 1:
		stepDrawType_ = Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_QUARTER);
		break;
	case 2:
		stepDrawType_ = Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_HALF);
		break;
	case 3:
		stepDrawType_ = Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_TURN);
		break;
	case 4:
		stepDrawType_ = Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_SPIN);
		break;
	}

}
