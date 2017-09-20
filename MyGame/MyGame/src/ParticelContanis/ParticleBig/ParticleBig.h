#ifndef PARTICLE_BIG_H_
#define PARTICLE_BIG_H_

#include "../Particle/Particle.h"

//大パーティクルクラス
class ParticleBig : public Particle {
public:
	//コンストラクタ
	ParticleBig(ParticleMediator& mediator);
	//更新
	virtual void update(float deltaTime);
	//クローン生成
	virtual ParticleBig* clone() const;
};
#endif // !PARTICLE_BIG_H_
