#include "ParticleMiddle.h"
#include "../ParticleMediator/ParticleMediator.h"
#include "../../Math/Random.h"

ParticleMiddle::ParticleMiddle(ParticleMediator & mediator)
:Particle(mediator),
m_Timer(0){
	m_Timer = Random::GetInstance().Range(25.0f, 30.0f);
}

void ParticleMiddle::update(float deltaTime){
	//親クラスの更新処理
	Particle::update(deltaTime);
	//移動量に空気抵抗を与える
	m_Velocity -= m_Velocity * 0.006f * deltaTime;
	//小パーティクルを生成する
	auto s = m_Mediator.generate("ParticleSmall");
	s->setTextureID(m_TextureID);
	//小パーティクルの初期位置を設定
	s->setPosition(m_Position);
	//自分の移動量の1/10を小パーティクルの移動量にする
	s->setVelocity(m_Velocity * 0.1f);
	//消滅タイマーを更新
	m_Timer -= deltaTime;
	//消滅時間が0になったらパーティクルを消去
	m_IsDaed = (m_Timer <= 0.0f);
}

ParticleMiddle * ParticleMiddle::clone() const
{
	return new ParticleMiddle(*this);
}
