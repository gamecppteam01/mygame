#pragma once
#include"UI.h"

class UITemplate:public UI {
public:
	//�R���X�g���N�^
	UITemplate(const Vector2& position);

	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw() const override;

};