#include "ParticleSmall.h"
#include"../../Math/Random.h"

ParticleSmall::ParticleSmall(ParticleMediator & mediator)
:Particle(mediator),
m_Timer(0){
	m_Timer = Random::GetInstance().Range(15.0f,20.0f);
}

void ParticleSmall::update(float deltaTime){
	//親クラスの更新処理
	Particle::update(deltaTime);
	//移動量に空気抵抗を与える
	m_Velocity -= m_Velocity * 0.006f * deltaTime; 
	//消滅タイマーを更新
	m_Timer -= deltaTime;
	//消滅時間が0になったらパーティクルを消去
	m_IsDaed = (m_Timer <= 0.0f);
}

ParticleSmall * ParticleSmall::clone() const
{
	return new ParticleSmall(*this);
}
