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
}

void Appear_StepUI::Update(float deltaTime){
}

void Appear_StepUI::Draw(const Vector3 & position) const{
	if (player_->getState() == Player::Player_State::Step) {
		switch (player_->getStep())
		{
		case 1:
			DrawSprite3D(position, 12.5f, Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_QUARTER),255,255,255,100);
			break;
		case 2:
			DrawSprite3D(position, 12.5f, Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_HALF));
			break;
		case 3:
			DrawSprite3D(position, 12.5f, Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_TURN));
			break;
		case 4:
			DrawSprite3D(position, 12.5f, Sprite::GetInstance().GetHandle(SPRITE_ID::APPEAR_STEP_SPIN));
			break;
		}
	}
}
