#include "ParticleBig.h"
#include "../ParticleMediator/ParticleMediator.h"
#include "../../Math/Random.h"

//コンストラクタ
ParticleBig::ParticleBig(ParticleMediator & mediator)
	:Particle(mediator) {
	//移動量を設定する
	m_Velocity.y = Random::GetInstance().Range(0.4f, 1.0f);
}

//更新
void ParticleBig::update(float deltaTime) {
	//親クラスの更新処理
	Particle::update(deltaTime);
	//小パーティクルの生成
	auto s = m_Mediator.generate("ParticleSmall");
	//小パーティクルの初期位置を設定
	s->setPosition(m_Position);
	//自分の移動量1/10を小パーティクルの移動量にする
	s->setVelocity(m_Velocity * 0.1f);
	s->setTextureID(m_TextureID);
	//頂上まで上がったか？
	if (m_Velocity.y <= 0.0f) {
		for (float pitch = 0.0f; pitch < 360.0f; pitch += 45.0f) {
			for (float yaw = 0.0f; yaw < 360.0f; yaw += 45.0f) {
				//中パーティクルを生成する
				auto m = m_Mediator.generate("ParticleMiddle");
				//中パーティクルの座標を設定
				m->setPosition(m_Position);
				m->setTextureID(m_TextureID);
				//中パーティクルをの移動量を設定
				auto v = Vector3::CreateFromYawPitch(pitch + Random::GetInstance().Range(-5.0f, 5.0f),
					yaw + Random::GetInstance().Range(0.2f, 0.4f));
			}
		}
		//大パーティクルを消去させる
	}
}

//クローン生成
ParticleBig * ParticleBig::clone() const
{
	return new ParticleBig(*this);
}
