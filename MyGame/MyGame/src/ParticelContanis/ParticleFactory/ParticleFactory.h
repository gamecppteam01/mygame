#ifndef PARTICLE_FACTORY_H_
#define PARTICLE_FACTORY_H_

#include "../Particle/Particle.h"
#include "Factory.h"

#include<string>

class ParticleMediator;//����҃N���X�̑O���Q��

//�p�[�e�B�N���H��N���X
class ParticleFactory : public Factory<Particle> {
public:
	//������
	void initialize(ParticleMediator& mediator);
};
#endif // !PARTICLE_FACTORY_H_
