#ifndef PARTICLE_SMALL_H_
#define PARTOCLE_SMALL_H_

#include"../Particle/Particle.h"

//���p�[�e�B�N���N���X
class ParticleSmall : public Particle {
public:
	//�R���X�g���N�^
	ParticleSmall(ParticleMediator& mediator);
	//�X�V
	virtual void update(float deltaTime) override;
	//�N���[���̐���
	virtual ParticleSmall* clone() const override;

private:
	//���Ń^�C�}�[
	float	m_Timer;
};
#endif // !PARTICLE_SMALL_H_
