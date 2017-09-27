#pragma once
#include"../Graphic/Model.h"
#include"../Math/Vector3.h"

class Effect {
public:
	Effect(MODEL_ID id,float maxFrame,float size, float firstFrame = 0.0f);
	virtual ~Effect(){}
	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw(const Vector3& position)const;

	bool isEnd()const;
protected:
	//�`��G�t�F�N�g(2D�X�v���C�g)
	MODEL_ID id_;
	//���݃t���[��
	float frame_;
	//�ő�t���[��
	float maxFrame_;
	//���݃G�t�F�N�g�T�C�Y
	float size_;
	//�I���t���O
	bool isEnd_;
	//��{�ʒu�ɉ��Z����x�N�g��
	Vector3 addPosition_;
};