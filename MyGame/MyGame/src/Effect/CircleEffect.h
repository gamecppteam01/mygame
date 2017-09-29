#pragma once
#include"Effect.h"

class CircleEffect :public Effect {
public:
	CircleEffect(float maxSize,float effectTime);
	virtual void Update(float deltaTime) override;
	virtual void Draw(const Vector3& position)const override;

private:
	//縮小エフェクト
	void EffectUpdate(float deltaTime);
	//拡大エフェクト
	void ToHoldUpdate(float deltaTime);
	//固定エフェクト
	void HoldUpdate(float deltaTime);
private:
	//エフェクトの最大サイズ
	float maxSize_;
	//収縮エフェクトの時間
	float effectTime_;
	//収縮エフェクトの最大時間
	float effectMaxTime_;

	//最終エフェクトの持続時間
	float holdTime_;

	//エフェクトの状態0からEffect->ToHold->Holdの順番
	int effectMode_;
};