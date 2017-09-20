#pragma once

#include"../ParticlePtr/ParticlePtr.h"
#include<list>
#include<string>
#include<memory>
#include"../ParticleMediator/ParticleMediator.h"
#include"../ParticleFactory/ParticleFactory.h"

class ParticleManager : public ParticleMediator{
public:
	//コンストラクタ
	ParticleManager();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;
	//追加	
	void add(const ParticlePtr& particle);
	//
	virtual ParticlePtr generate(const std::string& name);

private:
	//コピー禁止
	ParticleManager(const ParticleManager& othre);
	ParticleManager& operator = (const ParticleManager& other) = delete;

private:
	using ParticleContainer = std::list<ParticlePtr>;
	ParticleContainer m_ParticleContainer;

	using ParticleFactoryPtr = std::unique_ptr<ParticleFactory>;
	ParticleFactoryPtr m_Factory;
};
