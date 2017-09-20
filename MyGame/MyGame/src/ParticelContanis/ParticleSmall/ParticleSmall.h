#ifndef PARTICLE_SMALL_H_
#define PARTOCLE_SMALL_H_

#include"../Particle/Particle.h"

//小パーティクルクラス
class ParticleSmall : public Particle {
public:
	//コンストラクタ
	ParticleSmall(ParticleMediator& mediator);
	//更新
	virtual void update(float deltaTime) override;
	//クローンの生成
	virtual ParticleSmall* clone() const override;

private:
	//消滅タイマー
	float	m_Timer;
};
#endif // !PARTICLE_SMALL_H_
