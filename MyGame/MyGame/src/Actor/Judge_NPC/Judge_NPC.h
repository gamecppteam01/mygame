#pragma once
#include"../Actor.h"

enum class EventMessage;

class Judge_NPC : public Actor {
public:
	//コンストラクタ
	Judge_NPC(IWorld* world, const std::string& name, const Vector3& position,float scope_angle = 45.0f);
	//初期化
	virtual void initialize()override;
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);

private:
	bool is_Scorp_Angle() const;

private:
	//視野角
	float m_Scope_angle;
	//横回転角
	float yaw;
	//角度
	float m_Angle;
	//加算の値
	float m_Add;
};