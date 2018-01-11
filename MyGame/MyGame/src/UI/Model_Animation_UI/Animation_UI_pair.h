#pragma once

#include"../../Graphic/AnimationDx.h"
#include"../../Math/Math.h"
#include "../../Game/ID.h"

class Animaton_UI_Pair {
public:
	//コンストラクタ
	Animaton_UI_Pair(MODEL_ID id, const Vector3& position);
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;

	void setPosition(Vector3& position);
	void setRotation(Matrix& rotation);
	void ChangeModel(MODEL_ID& id);
	void ChangeStep(int step);

private:
	//アニメーション
	AnimationDx animation_;
	//座標
	Vector3 position_;
	//行列
	Matrix rotation_;
};
