#pragma once

#include "DxLib.h"
#include <string>

// モデルのアニメーションクラス
class Animation {
public:
	// アニメーションパラメータ
	struct AnimParams{
		int mID;
		float mCount;
	};
	// コンストラクタ
	explicit Animation(const unsigned int &modelHandle_);
	// 更新処理
	void update(float deltaTime);
	// 更新の中身
	void process();
	// アニメーションの変更
	void changeAnim(int id, float speed);
	// アニメーションが終了したかどうか
	bool isAnimEnd();
	// 再生中のアニメーションの再生時間
	float animTime();
private:
	// モデルハンドル
	unsigned int mModelHandle;
	// アニメーション速度
	float mAnimSpeed;
	// アニメーションブレンド率
	float mAnimBlendRate;
	// 現在のアニメーションのパラメータ
	AnimParams mCurrAnim;
	// 前回のアニメーションのパラメータ
	AnimParams mPrevAnim;
	// 現在のアニメーションのID
	int mID;
};