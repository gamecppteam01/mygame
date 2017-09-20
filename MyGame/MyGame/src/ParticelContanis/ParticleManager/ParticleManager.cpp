#include "ParticleManager.h"
#include "../Particle/Particle.h"

#include<algorithm>
#include<functional>

//�R���X�g���N�^
ParticleManager::ParticleManager() {
}

//������
void ParticleManager::initialize() {
	//�S�p�[�e�B�N�����폜
	m_ParticleContainer.clear();
	//�t�@�N�g���[�̐���
	m_Factory = std::make_unique<ParticleFactory>();
	m_Factory->initialize(*this);
}

//�X�V
void ParticleManager::update(float deltaTime){
	//�S�p�[�e�B�N���̍X�V
	for (auto particle : m_ParticleContainer) {
		particle->update(deltaTime);
	}

	//���S���Ă���p�[�e�B�N���̍폜
	m_ParticleContainer.remove_if([](const ParticlePtr& particle) {return particle->isDaed(); });
}

//�`��
void ParticleManager::draw() const{
	//�S�p�[�e�B�N���̕`��
	for (auto particle : m_ParticleContainer) {
		particle->draw();
	}
}

//�p�[�e�B�N���̒ǉ�
void ParticleManager::add(const ParticlePtr & particle){
	m_ParticleContainer.push_back(particle);
}

ParticlePtr ParticleManager::generate(const std::string & name)
{
		//�p�[�e�B�N���𐶐�
	auto particle = m_Factory->create(name);

	//�p�[�e�B�N���}�l�[�W���[�ɒǉ�
	add(particle);

	return particle;
}
