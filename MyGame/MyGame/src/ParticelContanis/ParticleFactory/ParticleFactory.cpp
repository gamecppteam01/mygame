#include "ParticleFactory.h"
#include"../ParticleBig/ParticleBig.h"
#include"../ParticleMiddle/ParticleMiddle.h"
#include"../ParticleSmall/ParticleSmall.h"

void ParticleFactory::initialize(ParticleMediator & mediator)
{
	add("ParticleBig", std::make_shared<ParticleBig>(mediator));
	add("ParticleMiddle", std::make_shared<ParticleMiddle>(mediator));
	add("ParticleSmall", std::make_shared<ParticleSmall>(mediator));
}
