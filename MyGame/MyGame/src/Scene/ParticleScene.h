#pragma once
#include"Scene.h"
#include"../ParticelContanis/ParticleMediator/ParticleMediator.h"
#include"../ParticelContanis/ParticleManager/ParticleManager.h"
#include"../ParticelContanis/ParticleFactory/ParticleFactory.h"
#include<string>

//パーティクルシーン
class ParticleScene :public Scene, public ParticleMediator
{
public:
	ParticleScene();

	void start()override;
	void update(float deltaTime)override;
	void draw() const override;
	void end() override;

private:
	ParticlePtr generate(const std::string& name);

private:
	ParticleManager m_ParticleManager;
	ParticleFactory m_ParticleFactory;
	float m_GeneratTimer;
};