#include "ResultField.h"
#include"../../Graphic/Model.h"

ResultField::ResultField()
{
}

void ResultField::update(float deltaTime)
{
}

void ResultField::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::STAGE_MODEL, Matrix::Identity);
}
