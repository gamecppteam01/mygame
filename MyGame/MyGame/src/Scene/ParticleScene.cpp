#include "ParticleScene.h"
#include"../ParticelContanis/Particle/Particle.h"
#include"../Math/Random.h"

ParticleScene::ParticleScene()
	:m_GeneratTimer(0)
{
}

void ParticleScene::start()
{
	//パーティクル工場の初期化
	m_ParticleFactory.initialize(*this);

	//パーティクル管理者の初期化
	m_ParticleManager.initialize();
}

void ParticleScene::update(float deltaTime)
{
	//2秒毎にパーティクルを生成させる
	if (m_GeneratTimer >= 20.0f)
	{
		//大パーティクルを生成する
		auto big = generate("ParticleBig");
		Vector3 position;
		position.x = Random::GetInstance().Range(-15.0f, 15.0f);
		position.y = 0.0f;
		position.z = Random::GetInstance().Range(-20.0f, 20.0f);
		big->setPosition(position);
		int ID = Random::GetInstance().Range(0, 1);
		big->setTextureID(ID);
		//生成タイマーを初期化
		m_GeneratTimer = 0.0f;
	}

	//生成タイマーの更新
	m_GeneratTimer += 1;

	//パーティクルマネージャーの更新
	m_ParticleManager.update(deltaTime);
}

void ParticleScene::draw() const
{
	m_ParticleManager.draw();
}

void ParticleScene::end()
{
}

ParticlePtr ParticleScene::generate(const std::string & name)
{
	//パーティクルを生成
	auto particle = m_ParticleFactory.create(name);

	//パーティクルマネージャーに追加
	m_ParticleManager.add(particle);

	return particle;
}
