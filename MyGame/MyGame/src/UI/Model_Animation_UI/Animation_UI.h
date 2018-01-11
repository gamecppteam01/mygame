#pragma once

#include "../../Graphic/AnimationDx.h"
#include "../../Game/ID.h"
#include "../../Math/Math.h"
#include "Animation_UI_pair.h"
#include <memory>

class Animation_UI {
public:
	//�R���X�g���N�^
	Animation_UI(MODEL_ID id, const Vector3& position);
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw();

	void ChangeModel(MODEL_ID& id,MODEL_ID& id2);
	void ChangeStep(int step);
	void setPosition(Vector3& position);

private:
	//�p�[�g�i�[
	std::unique_ptr<Animaton_UI_Pair> pair_;
	//�A�j���[�V����
	AnimationDx animation_;
	//���W
	Vector3 position_;
	//��]
	Matrix rotation_;
	//���S���W
	Vector3 centerPosition_;
	//�j�Ə��̋���
	const Vector3 pairDistance{ 0.0f,0.0f,5.0f };
};