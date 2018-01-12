#include "ResultModelDrawer.h"
#include"../../Math/Matrix.h"
#include"../../Math/Vector3.h"
#include"../../Graphic/Model.h"

static const Vector3 lrPos{ 4.0f,0.0f,0.0f };

ResultModelDrawer::ResultModelDrawer()
{
}

void ResultModelDrawer::init()
{
}

void ResultModelDrawer::setModel(MODEL_ID right, MODEL_ID left)
{
	rightModel_.SetHandle(Model::GetInstance().GetHandle(right));
	leftModel_.SetHandle(Model::GetInstance().GetHandle(left));
}

void ResultModelDrawer::setAnim(int animNum, bool isLoop)
{
	isLoop_ = isLoop;
	animNum_ = animNum;
	rightModel_.ChangeAnim(animNum,0.0f,1.0f, false,1.0f,true);
	leftModel_.ChangeAnim(animNum,0.0f, 1.0f, false,1.0f,true);
}

void ResultModelDrawer::lastAnim()
{
	rightModel_.lastAnim();
	leftModel_.lastAnim();
}

void ResultModelDrawer::update(float deltaTime)
{
	rightModel_.Update(deltaTime);
	leftModel_.Update(deltaTime);

	if (isLoop_) {
		if (rightModel_.IsAnimEnd())rightModel_.ChangeAnim(animNum_, 0.0f, 1.0f, false, 1.0f, true);
		if (leftModel_.IsAnimEnd())leftModel_.ChangeAnim(animNum_, 0.0f, 1.0f, false, 1.0f, true);
	}
}

void ResultModelDrawer::draw(const Vector3& position, const Matrix& rotation)const
{
	Vector3 rightPosition_ = lrPos;
	Vector3 leftPosition_ = -lrPos;

	rightPosition_ = rightPosition_*rotation;
	leftPosition_ = leftPosition_*rotation;

	rightModel_.Draw(Matrix::CreateRotationY(90.0f)*Matrix(rotation).Translation(rightPosition_ + position));
	leftModel_.Draw(Matrix::CreateRotationY(-90.0f)*Matrix(rotation).Translation(leftPosition_ + position));
}

bool ResultModelDrawer::isEnd() const
{
	return rightModel_.IsAnimEnd() && leftModel_.IsAnimEnd();
}

float ResultModelDrawer::getMaxAnimTime() const
{
	return rightModel_.GetAnimMaxTime();
}
