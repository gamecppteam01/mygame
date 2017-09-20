#include "Particle.h"

#include"../../Graphic/Model.h"

//�p�[�e�B�N���̏d�͒l
const float Particle::GRAVITY = 0.005f;

//�R���X�g���N�^
Particle::Particle(ParticleMediator & mediator)
	:m_Mediator(mediator),
	m_TextureID(0),
	m_IsDaed(false),
	m_Position(Vector3::Zero),
	m_Velocity(Vector3::Zero),
	m_Origin({16.0f,16.0f}) {
}

//�e�N�X�`��ID��ݒ�
void Particle::setTextureID(unsigned int trxtureID)
{
	m_TextureID = trxtureID;
}

//���W��ݒ�
void Particle::setPosition(const Vector3 & position)
{
	m_Position = position;
}

//�ړ��ʂ�ݒ�
void Particle::setVelocity(const Vector3 & velocity)
{
	m_Velocity = velocity;
}

//�e�N�X�`��ID���擾
unsigned int Particle::getTextureID() const
{
	return m_TextureID;
}

//���W���擾
const Vector3 & Particle::getPosition() const
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return m_Position;
}

//�ړ��ʂ��擾
const Vector3 & Particle::getVelocity() const
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return m_Velocity;
}

//�N���[���̐���
Particle * Particle::clone() const
{
	return new Particle(*this);
}

//�X�V
void Particle::update(float deltaTime)
{
	//�p�[�e�B�N�����ړ�������
	m_Position += m_Velocity * deltaTime;

	//�ړ��ʂɏd�͂�������
	m_Velocity.y -= GRAVITY * deltaTime;

	//�p�[�e�B�N�����n�ʂɒ��������H
	m_IsDaed = (m_Position.y < 0.0f);
}

//�`��
void Particle::draw() const
{
	//Model::GetInstance().Draw2D(MODEL_ID::PARTICLE_MODEL, m_Position,0,32.0f,m_Origin);
}

//���S���Ă��邩�H
bool Particle::isDaed() const
{
	return m_IsDaed;
}
