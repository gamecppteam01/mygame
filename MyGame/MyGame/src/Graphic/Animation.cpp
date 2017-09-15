#include "Animation.h"

#include <math.h>

static const float ANIM_BLEND_SPEED = 0.1f;
//static const float PLAY_ANIM_SPEED = 0.8f;

// コンストラクタ
Animation::Animation(const unsigned int &modelHandle_) :
	mModelHandle(modelHandle_), mAnimSpeed(1.0f), mAnimBlendRate(1.0f), mCurrAnim({-1, 0}), mPrevAnim({ -1, 0 }), mID(-1){

}

// 更新処理
void Animation::update(float deltaTime){
	process();
}

// 更新の中身
void Animation::process(){
	float AnimTotalTime;		// 再生しているアニメーションの総時間

	// ブレンド率が１以下の場合は１に近づける
	if (mAnimBlendRate < 1.0f)
	{
		mAnimBlendRate += ANIM_BLEND_SPEED;
		if (mAnimBlendRate > 1.0f)
		{
			mAnimBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (mCurrAnim.mID != -1)
	{
		// アニメーションの総時間を取得
		AnimTotalTime = MV1GetAttachAnimTotalTime(mModelHandle, mCurrAnim.mID);

		// 再生時間を進める
		mCurrAnim.mCount += mAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (mCurrAnim.mCount >= AnimTotalTime)
		{
			mCurrAnim.mCount = fmodf(mCurrAnim.mCount, AnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(mModelHandle, mCurrAnim.mID, mCurrAnim.mCount);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(mModelHandle, mCurrAnim.mID, mAnimBlendRate);
	}

	// 再生しているアニメーション２の処理
	if (mPrevAnim.mID != -1)
	{
		// アニメーションの総時間を取得
		AnimTotalTime = MV1GetAttachAnimTotalTime(mModelHandle, mPrevAnim.mID);

		// 再生時間を進める
		mPrevAnim.mCount += mAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (mPrevAnim.mCount > AnimTotalTime)
		{
			mPrevAnim.mCount = fmodf(mPrevAnim.mCount, AnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(mModelHandle, mPrevAnim.mID, mPrevAnim.mCount);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(mModelHandle, mPrevAnim.mID, 1.0f - mAnimBlendRate);
	}
}

// アニメーションの変更
void Animation::changeAnim(int id, float speed){
	mAnimSpeed = speed;
	if (mID == id)return;
	mID = id;
	// 再生中のモーション２が有効だったらデタッチする
	if (mPrevAnim.mID != -1){
		MV1DetachAnim(mModelHandle, mPrevAnim.mID);
		mPrevAnim.mID = -1;
	}

	// 今まで再生中のモーション１だったものの情報を２に移動する
	mPrevAnim = mCurrAnim;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	mCurrAnim.mID = MV1AttachAnim(mModelHandle, id);
	mCurrAnim.mCount = 0.0f;

	// ブレンド率は再生中のモーション２が有効ではない場合は１．０ｆ( 再生中のモーション１が１００％の状態 )にする
	mAnimBlendRate = mPrevAnim.mID == -1 ? 1.0f : 0.0f;
}

// アニメーションが終了したかどうか
bool Animation::isAnimEnd(){
	return 	mCurrAnim.mCount >= animTime() - 1;
}

// 再生中のアニメーションの再生時間
float Animation::animTime(){
	return MV1GetAttachAnimTotalTime(mModelHandle, mCurrAnim.mID);
}
