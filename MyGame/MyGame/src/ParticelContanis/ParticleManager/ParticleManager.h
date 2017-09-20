#pragma once

#include"../ParticlePtr/ParticlePtr.h"
#include<list>
#include<string>
#include<memory>
#include"../ParticleMediator/ParticleMediator.h"
#include"../ParticleFactory/ParticleFactory.h"

class ParticleManager : public ParticleMediator{
public:
	//�R���X�g���N�^
	ParticleManager();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw() const;
	//�ǉ�	
	void add(const ParticlePtr& particle);
	//
	virtual ParticlePtr generate(const std::string& name);

private:
	//�R�s�[�֎~
	ParticleManager(const ParticleManager& othre);
	ParticleManager& operator = (const ParticleManager& other) = delete;

private:
	using ParticleContainer = std::list<ParticlePtr>;
	ParticleContainer m_ParticleContainer;

	using ParticleFactoryPtr = std::unique_ptr<ParticleFactory>;
	ParticleFactoryPtr m_Factory;
};
