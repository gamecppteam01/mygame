#pragma once

#include"../../Graphic/AnimationDx.h"
#include"../../Math/Math.h"
#include "../../Game/ID.h"

class Animaton_UI_Pair {
public:
	//�R���X�g���N�^
	Animaton_UI_Pair(MODEL_ID id, const Vector3& position);
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;

	void setPosition(Vector3& position);
	void setRotation(Matrix& rotation);
	void ChangeModel(MODEL_ID& id);
	void ChangeStep(int step);

private:
	//�A�j���[�V����
	AnimationDx animation_;
	//���W
	Vector3 position_;
	//�s��
	Matrix rotation_;
};
