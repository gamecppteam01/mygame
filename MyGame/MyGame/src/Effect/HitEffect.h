#pragma once
#include"Effect.h"

class HitEffect :public Effect {
public:
	HitEffect(float maxSize,int effectCount, float effectTime);
	virtual void Update(float deltaTime) override;
	virtual void Draw(const Vector3& position)const override;

private:
	//エフェクトの生成数
	int effectCount_;
	//エフェクトの最大サイズ
	float maxSize_;
	//エフェクトの全時間
	float timeCount_;
	//収縮エフェクトの最大時間
	float effectMaxTime_;
};