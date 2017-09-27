#pragma once
#include"../Graphic/Model.h"
#include"../Math/Vector3.h"

class Effect {
public:
	Effect(MODEL_ID id,float maxFrame,float size, float firstFrame = 0.0f);
	virtual ~Effect(){}
	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw(const Vector3& position)const;

	bool isEnd()const;
protected:
	//描画エフェクト(2Dスプライト)
	MODEL_ID id_;
	//現在フレーム
	float frame_;
	//最大フレーム
	float maxFrame_;
	//現在エフェクトサイズ
	float size_;
	//終了フラグ
	bool isEnd_;
	//基本位置に加算するベクトル
	Vector3 addPosition_;
};