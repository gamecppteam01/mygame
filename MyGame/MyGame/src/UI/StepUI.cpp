#include "StepUI.h"

StepUI::StepUI(const SPRITE_ID & id,const Vector2 & position
	,const Vector2& origin,float alpha,const Vector2& scale)
	:UI{ "StepUI",position }, ID_(id), position_(position),origin_(origin),alpha_(alpha),scale_(scale){
}

void StepUI::initialize(){
}

void StepUI::update(float deltaTime){
	//Ç±Ç±Ç…UIÇÃââèoÇ
}

void StepUI::draw() const{
	Sprite::GetInstance().Draw(ID_, position_, origin_, alpha_, scale_);
}

void StepUI::end(){
}
