#ifndef PARTICLE_MIDDEL_H_
#define PARTICLE_MIDDEL_H_

#include"../Particle/Particle.h"

//中パーティクルクラス
class ParticleMiddle : public Particle {
public:
	//コンストラクタ
	ParticleMiddle(ParticleMediator& mediator);
	//更新
	virtual void update(float deltaTime) override;
	//クローンの生成
	virtual ParticleMiddle* clone() const;

private:
	//消滅タイマー
	float	m_Timer;
};
#endif // !PARTICLE_MIDDEL_H_
