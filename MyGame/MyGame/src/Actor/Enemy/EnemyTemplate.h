#pragma once
#include"Enemy.h"
//カプセル判定を利用しない場合はBoundingCapsuleのincludeは必要ない
#include"../Body/BoundingCapsule.h"
//エネミーのテンプレートクラス
class EnemyTemplate :public Enemy {
public:
	//カプセル判定は例、キャラクターの体型に応じて設定を変更する事
	EnemyTemplate(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body= std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param) override;
	// 更新
	virtual void onUpdate(float deltaTime)override;
	// 描画
	virtual void onDraw() const override;
	// 衝突した
	virtual void onCollide(Actor& other) override;

private:
};
