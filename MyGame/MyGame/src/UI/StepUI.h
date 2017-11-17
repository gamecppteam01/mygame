#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include "../UI/UI.h"

class StepUI : public UI {
public:
	StepUI(const SPRITE_ID& id,const Vector2& position);
	void initialize() override;
	void update(float deltaTime) override;
	void draw() const override;

private:
	//�X�e�b�vUI�̍��W
	Vector2 position_;
	//�X�e�b�vUI�̌��_
	Vector2 origin_;
	//�X�e�b�vUI�̃T�C�Y
	Vector2 scale_;
	//�X�e�b�vUI�̃A���t�@�l
	float alpha_;
	//�X�e�b�vUI�̉摜ID
	SPRITE_ID ID_;
};