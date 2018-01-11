#pragma once

#include "../../Graphic/AnimationDx.h"
#include "../../Game/ID.h"
#include "../../Math/Math.h"
#include "Animation_UI_pair.h"
#include <memory>

class Animation_UI {
public:
	//コンストラクタ
	Animation_UI(MODEL_ID id, const Vector3& position);
	//更新
	void Update(float deltaTime);
	//描画
	void Draw();

	void ChangeModel(MODEL_ID& id,MODEL_ID& id2);
	void ChangeStep(int step);
	void setPosition(Vector3& position);

private:
	//パートナー
	std::unique_ptr<Animaton_UI_Pair> pair_;
	//アニメーション
	AnimationDx animation_;
	//座標
	Vector3 position_;
	//回転
	Matrix rotation_;
	//中心座標
	Vector3 centerPosition_;
	//男と女の距離
	const Vector3 pairDistance{ 0.0f,0.0f,5.0f };
};