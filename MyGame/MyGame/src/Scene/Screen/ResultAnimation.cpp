#include "ResultAnimation.h"
#include"../../Graphic/Model.h"

ResultAnimation::ResultAnimation():animation_(){
	
}

void ResultAnimation::initialize(){
	rotation = Matrix::Identity;
}

void ResultAnimation::set(const int & handle, const int & handle2){
	animation_.SetHandle(handle);
	animation2_.SetHandle(handle2);
}

void ResultAnimation::update(float deltaTime){
	animation_.Update(deltaTime);
	animation2_.Update(deltaTime);
}

void ResultAnimation::draw(const Vector3& position) const{
	animation_.Draw(Matrix(rotation).Translation(Vector3{position.x+1,position.y,position.z+1}));
	animation2_.Draw((Matrix::CreateRotationY(180.0f))*Matrix(rotation).Translation(Vector3{ position.x-1,position.y,position.z-1 }));
}

void ResultAnimation::animation(){
	animation_.setAnimSpeed(50.0f);
	animation2_.setAnimSpeed(50.0f);
	animation_.ChangeAnim(2, 0.0f, 1.0f, true, 1.0f, true);
	animation_.setLoop(false);
	animation2_.ChangeAnim(2, 0.0f, 1.0f, true, 1.0f, true);
	animation2_.setLoop(false);
}

bool ResultAnimation::end() const{
	if (animation_.IsAnimEnd()) return true;
	return false;
}
