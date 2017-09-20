#include "ParticleSmall.h"
#include"../../Math/Random.h"

ParticleSmall::ParticleSmall(ParticleMediator & mediator)
:Particle(mediator),
m_Timer(0){
	m_Timer = Random::GetInstance().Range(15.0f,20.0f);
}

void ParticleSmall::update(float deltaTime){
	//�e�N���X�̍X�V����
	Particle::update(deltaTime);
	//�ړ��ʂɋ�C��R��^����
	m_Velocity -= m_Velocity * 0.006f * deltaTime; 
	//���Ń^�C�}�[���X�V
	m_Timer -= deltaTime;
	//���Ŏ��Ԃ�0�ɂȂ�����p�[�e�B�N��������
	m_IsDaed = (m_Timer <= 0.0f);
}

ParticleSmall * ParticleSmall::clone() const
{
	return new ParticleSmall(*this);
}
