#pragma once

#include"DxLib.h"

#include"../../Math/Math.h"

class ParticleMediator;

//�p�[�e�B�N���N���X
class Particle {
protected:
	Particle(ParticleMediator& mediator);
	//�e�N���X��p�ɂ���
public:
	virtual ~Particle(){}
	void setTextureID(unsigned int trxtureID);	//�e�N�X�`��ID�̐ݒ�
	void setPosition(const Vector3& position);	//���W��ݒ�
	void setVelocity(const Vector3& velocity);	//�ړ��ʂ�ݒ�
	unsigned int getTextureID() const;			//�e�N�X�`��ID���擾
	const Vector3& getPosition() const;			//���W���擾
	const Vector3& getVelocity() const;			//�ړ��ʂ��擾

	//�N���[������
	virtual Particle* clone() const;//<-const������ƃI�[�o�[���C�h�����ɂȂ�
	virtual void update(float deltaTime);				//�X�V
	virtual void draw() const;					//�`��

	bool isDaed() const;						//���S���Ă��邩�H

protected:
	static const float GRAVITY;					//�d��

	//�����
	ParticleMediator&	m_Mediator;		
	unsigned int		m_TextureID;	//�e�N�X�`��ID
	bool				m_IsDaed;		//���S�t���O
	Vector3				m_Position;		//���W
	Vector3				m_Velocity;		//�ړ���
	Vector2				m_Origin;		//���_
};
