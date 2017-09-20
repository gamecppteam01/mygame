#ifndef PARTICLE_MIDDEL_H_
#define PARTICLE_MIDDEL_H_

#include"../Particle/Particle.h"

//���p�[�e�B�N���N���X
class ParticleMiddle : public Particle {
public:
	//�R���X�g���N�^
	ParticleMiddle(ParticleMediator& mediator);
	//�X�V
	virtual void update(float deltaTime) override;
	//�N���[���̐���
	virtual ParticleMiddle* clone() const;

private:
	//���Ń^�C�}�[
	float	m_Timer;
};
#endif // !PARTICLE_MIDDEL_H_
