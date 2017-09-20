#ifndef PARTICLE_PTR_H_
#define PARTICLE_PTR_H_

#include<memory>

//パーティクルポインタ
class Particle;
using ParticlePtr = std::shared_ptr<Particle>;

#endif // !PARTICLE_PTR_H_
