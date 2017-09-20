#include "ParticleManager.h"
#include "../Particle/Particle.h"

#include<algorithm>
#include<functional>

//コンストラクタ
ParticleManager::ParticleManager() {
}

//初期化
void ParticleManager::initialize() {
	//全パーティクルを削除
	m_ParticleContainer.clear();
	//ファクトリーの生成
	m_Factory = std::make_unique<ParticleFactory>();
	m_Factory->initialize(*this);
}

//更新
void ParticleManager::update(float deltaTime){
	//全パーティクルの更新
	for (auto particle : m_ParticleContainer) {
		particle->update(deltaTime);
	}

	//死亡しているパーティクルの削除
	m_ParticleContainer.remove_if([](const ParticlePtr& particle) {return particle->isDaed(); });
}

//描画
void ParticleManager::draw() const{
	//全パーティクルの描画
	for (auto particle : m_ParticleContainer) {
		particle->draw();
	}
}

//パーティクルの追加
void ParticleManager::add(const ParticlePtr & particle){
	m_ParticleContainer.push_back(particle);
}

ParticlePtr ParticleManager::generate(const std::string & name)
{
		//パーティクルを生成
	auto particle = m_Factory->create(name);

	//パーティクルマネージャーに追加
	add(particle);

	return particle;
}
