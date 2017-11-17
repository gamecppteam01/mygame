#include "StepUI.h"

StepUI::StepUI(const SPRITE_ID & id,const Vector2 & position)
	:UI{ "StepUI",position }, ID_(id){
}

void StepUI::initialize(){
	origin_ = Sprite::GetInstance().GetSize(ID_) / 2;
	alpha_ = 1.0f;
	scale_ = Vector2::One;
}

void StepUI::update(float deltaTime){
	//Ç±Ç±Ç…UIÇÃââèoÇ
}

void StepUI::draw() const{
	Sprite::GetInstance().Draw(ID_, position_, origin_, alpha_, scale_);
}
