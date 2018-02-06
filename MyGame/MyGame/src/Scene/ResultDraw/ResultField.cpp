#include "ResultField.h"
#include"../../Graphic/Model.h"
#include"../../Field/Field.h"

ResultField::ResultField()
{
}
void ResultField::init() {
	field_ = std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), Model::GetInstance().GetHandle(MODEL_ID::SKYBOX_MODEL));
}
void ResultField::update(float deltaTime)
{
	field_->update(deltaTime);
}

void ResultField::draw() const
{
	field_->draw();
}

void ResultField::setBright(float r, float g, float b)
{
	field_->AudienceLightColor(r, g, b);
}
