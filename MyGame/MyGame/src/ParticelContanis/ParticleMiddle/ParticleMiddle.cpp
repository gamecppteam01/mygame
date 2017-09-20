#include "ParticleMiddle.h"
#include "../ParticleMediator/ParticleMediator.h"
#include "../../Math/Random.h"

ParticleMiddle::ParticleMiddle(ParticleMediator & mediator)
:Particle(mediator),
m_Timer(0){
	m_Timer = Random::GetInstance().Range(25.0f, 30.0f);
}

void ParticleMiddle::update(float deltaTime){
	//�e�N���X�̍X�V����
	Particle::update(deltaTime);
	//�ړ��ʂɋ�C��R��^����
	m_Velocity -= m_Velocity * 0.006f * deltaTime;
	//���p�[�e�B�N���𐶐�����
	auto s = m_Mediator.generate("ParticleSmall");
	s->setTextureID(m_TextureID);
	//���p�[�e�B�N���̏����ʒu��ݒ�
	s->setPosition(m_Position);
	//�����̈ړ��ʂ�1/10�����p�[�e�B�N���̈ړ��ʂɂ���
	s->setVelocity(m_Velocity * 0.1f);
	//���Ń^�C�}�[���X�V
	m_Timer -= deltaTime;
	//���Ŏ��Ԃ�0�ɂȂ�����p�[�e�B�N��������
	m_IsDaed = (m_Timer <= 0.0f);
}

ParticleMiddle * ParticleMiddle::clone() const
{
	return new ParticleMiddle(*this);
}
