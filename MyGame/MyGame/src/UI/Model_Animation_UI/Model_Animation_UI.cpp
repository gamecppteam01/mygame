#include "Model_Animation_UI.h"
#include <algorithm>

void Model_Animation_UI::initialize(){
	//animations_.clear();
	anm_ui_ptr = std::make_unique<Animation_UI>(MODEL_ID::BALANCEENEMY_MODEL, Vector3(-23.0f, -15.0f, 40.0f));
}

void Model_Animation_UI::Updata(float deltaTime){
	//for (auto a : animations_) {
	//	a->Update(deltaTime);
	//}
	anm_ui_ptr->Update(deltaTime);
}

void Model_Animation_UI::Draw() const{
	//for (auto a : animations_) {
	//	a->Draw();
	//}
	anm_ui_ptr->Draw();
}

void Model_Animation_UI::UseModelAnimation(MODEL_ID& id,MODEL_ID& id2,int step){
	//Anima_UI_Ptr animation = std::make_shared<Animation_UI>(id, position);
	//animations_.push_back(animation);
	anm_ui_ptr->ChangeModel(id,id2);
	//anm_ui_ptr->ChangeStep(step);
}

Vector3 Model_Animation_UI::getPosition() const
{
	return anm_ui_ptr->getPosition();
}

Vector3 Model_Animation_UI::getCenter() const{
	return anm_ui_ptr->getCenter();
}

void Model_Animation_UI::setCenter(Vector3 & center)
{
	anm_ui_ptr->setCenter(center);
}

int Model_Animation_UI::getModelHandle() const
{
	return anm_ui_ptr->getModelHandle();
}

void Model_Animation_UI::setPosition(Vector3 & position){
	anm_ui_ptr->setPosition(position);
}
