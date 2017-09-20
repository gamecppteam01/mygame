#ifndef PARTICLE_FACTORY_H_
#define PARTICLE_FACTORY_H_

#include "../Particle/Particle.h"
#include "Factory.h"

#include<string>

class ParticleMediator;//仲介者クラスの前方参照

//パーティクル工場クラス
class ParticleFactory : public Factory<Particle> {
public:
	//初期化
	void initialize(ParticleMediator& mediator);
};
#endif // !PARTICLE_FACTORY_H_
