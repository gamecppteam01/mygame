#include "Effect.h"

Effect::Effect(MODEL_ID id, float maxFrame, float size, float firstFrame):
	id_(id),frame_(firstFrame),maxFrame_(maxFrame),size_(size), isEnd_(false), addPosition_(Vector3::Zero)
{
	Initialize();
}

void Effect::Initialize()
{
}

void Effect::Update(float deltaTime)
{
}

void Effect::Draw(const Vector3& position)const
{
	if (isEnd_)return;

	Model::GetInstance().Draw2D(id_, position+addPosition_, frame_, size_);
}

void Effect::Draw(const Vector3 & position, const Vector2 & origin, float alpha, float angle) const
{
	if (isEnd_)return;

	Model::GetInstance().Draw2D(id_, position + addPosition_, frame_, size_,origin,angle,alpha);
}

bool Effect::isEnd() const
{
	return isEnd_;
}
