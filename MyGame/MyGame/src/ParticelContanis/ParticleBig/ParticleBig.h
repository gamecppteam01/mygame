#ifndef PARTICLE_BIG_H_
#define PARTICLE_BIG_H_

#include "../Particle/Particle.h"

//��p�[�e�B�N���N���X
class ParticleBig : public Particle {
public:
	//�R���X�g���N�^
	ParticleBig(ParticleMediator& mediator);
	//�X�V
	virtual void update(float deltaTime);
	//�N���[������
	virtual ParticleBig* clone() const;
};
#endif // !PARTICLE_BIG_H_
