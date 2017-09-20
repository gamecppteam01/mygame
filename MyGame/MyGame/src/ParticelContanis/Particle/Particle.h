#pragma once

#include"DxLib.h"

#include"../../Math/Math.h"

class ParticleMediator;

//パーティクルクラス
class Particle {
protected:
	Particle(ParticleMediator& mediator);
	//親クラス専用にする
public:
	virtual ~Particle(){}
	void setTextureID(unsigned int trxtureID);	//テクスチャIDの設定
	void setPosition(const Vector3& position);	//座標を設定
	void setVelocity(const Vector3& velocity);	//移動量を設定
	unsigned int getTextureID() const;			//テクスチャIDを取得
	const Vector3& getPosition() const;			//座標を取得
	const Vector3& getVelocity() const;			//移動量を取得

	//クローン生成
	virtual Particle* clone() const;//<-constをつけるとオーバーライド扱いになる
	virtual void update(float deltaTime);				//更新
	virtual void draw() const;					//描画

	bool isDaed() const;						//死亡しているか？

protected:
	static const float GRAVITY;					//重力

	//仲介者
	ParticleMediator&	m_Mediator;		
	unsigned int		m_TextureID;	//テクスチャID
	bool				m_IsDaed;		//死亡フラグ
	Vector3				m_Position;		//座標
	Vector3				m_Velocity;		//移動量
	Vector2				m_Origin;		//原点
};
