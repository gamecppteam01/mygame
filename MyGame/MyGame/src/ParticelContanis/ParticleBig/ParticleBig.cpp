#include "ParticleBig.h"
#include "../ParticleMediator/ParticleMediator.h"
#include "../../Math/Random.h"

//�R���X�g���N�^
ParticleBig::ParticleBig(ParticleMediator & mediator)
	:Particle(mediator) {
	//�ړ��ʂ�ݒ肷��
	m_Velocity.y = Random::GetInstance().Range(0.4f, 1.0f);
}

//�X�V
void ParticleBig::update(float deltaTime) {
	//�e�N���X�̍X�V����
	Particle::update(deltaTime);
	//���p�[�e�B�N���̐���
	auto s = m_Mediator.generate("ParticleSmall");
	//���p�[�e�B�N���̏����ʒu��ݒ�
	s->setPosition(m_Position);
	//�����̈ړ���1/10�����p�[�e�B�N���̈ړ��ʂɂ���
	s->setVelocity(m_Velocity * 0.1f);
	s->setTextureID(m_TextureID);
	//����܂ŏオ�������H
	if (m_Velocity.y <= 0.0f) {
		for (float pitch = 0.0f; pitch < 360.0f; pitch += 45.0f) {
			for (float yaw = 0.0f; yaw < 360.0f; yaw += 45.0f) {
				//���p�[�e�B�N���𐶐�����
				auto m = m_Mediator.generate("ParticleMiddle");
				//���p�[�e�B�N���̍��W��ݒ�
				m->setPosition(m_Position);
				m->setTextureID(m_TextureID);
				//���p�[�e�B�N�����̈ړ��ʂ�ݒ�
				auto v = Vector3::CreateFromYawPitch(pitch + Random::GetInstance().Range(-5.0f, 5.0f),
					yaw + Random::GetInstance().Range(0.2f, 0.4f));
			}
		}
		//��p�[�e�B�N��������������
	}
}

//�N���[������
ParticleBig * ParticleBig::clone() const
{
	return new ParticleBig(*this);
}
