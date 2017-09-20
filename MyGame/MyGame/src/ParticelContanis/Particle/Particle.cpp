#include "Particle.h"

#include"../../Graphic/Model.h"

//パーティクルの重力値
const float Particle::GRAVITY = 0.005f;

//コンストラクタ
Particle::Particle(ParticleMediator & mediator)
	:m_Mediator(mediator),
	m_TextureID(0),
	m_IsDaed(false),
	m_Position(Vector3::Zero),
	m_Velocity(Vector3::Zero),
	m_Origin({16.0f,16.0f}) {
}

//テクスチャIDを設定
void Particle::setTextureID(unsigned int trxtureID)
{
	m_TextureID = trxtureID;
}

//座標を設定
void Particle::setPosition(const Vector3 & position)
{
	m_Position = position;
}

//移動量を設定
void Particle::setVelocity(const Vector3 & velocity)
{
	m_Velocity = velocity;
}

//テクスチャIDを取得
unsigned int Particle::getTextureID() const
{
	return m_TextureID;
}

//座標を取得
const Vector3 & Particle::getPosition() const
{
	// TODO: return ステートメントをここに挿入します
	return m_Position;
}

//移動量を取得
const Vector3 & Particle::getVelocity() const
{
	// TODO: return ステートメントをここに挿入します
	return m_Velocity;
}

//クローンの生成
Particle * Particle::clone() const
{
	return new Particle(*this);
}

//更新
void Particle::update(float deltaTime)
{
	//パーティクルを移動させる
	m_Position += m_Velocity * deltaTime;

	//移動量に重力を加える
	m_Velocity.y -= GRAVITY * deltaTime;

	//パーティクルが地面に着いたか？
	m_IsDaed = (m_Position.y < 0.0f);
}

//描画
void Particle::draw() const
{
	//Model::GetInstance().Draw2D(MODEL_ID::PARTICLE_MODEL, m_Position,0,32.0f,m_Origin);
}

//死亡しているか？
bool Particle::isDaed() const
{
	return m_IsDaed;
}
