#include "ParticleScene.h"
#include"../ParticelContanis/Particle/Particle.h"
#include"../Math/Random.h"

ParticleScene::ParticleScene()
	:m_GeneratTimer(0)
{
}

void ParticleScene::start()
{
	//�p�[�e�B�N���H��̏�����
	m_ParticleFactory.initialize(*this);

	//�p�[�e�B�N���Ǘ��҂̏�����
	m_ParticleManager.initialize();
}

void ParticleScene::update(float deltaTime)
{
	//2�b���Ƀp�[�e�B�N���𐶐�������
	if (m_GeneratTimer >= 20.0f)
	{
		//��p�[�e�B�N���𐶐�����
		auto big = generate("ParticleBig");
		Vector3 position;
		position.x = Random::GetInstance().Range(-15.0f, 15.0f);
		position.y = 0.0f;
		position.z = Random::GetInstance().Range(-20.0f, 20.0f);
		big->setPosition(position);
		int ID = Random::GetInstance().Range(0, 1);
		big->setTextureID(ID);
		//�����^�C�}�[��������
		m_GeneratTimer = 0.0f;
	}

	//�����^�C�}�[�̍X�V
	m_GeneratTimer += 1;

	//�p�[�e�B�N���}�l�[�W���[�̍X�V
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
	//�p�[�e�B�N���𐶐�
	auto particle = m_ParticleFactory.create(name);

	//�p�[�e�B�N���}�l�[�W���[�ɒǉ�
	m_ParticleManager.add(particle);

	return particle;
}
