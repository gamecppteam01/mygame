#pragma once
#include"../Actor.h"


class Judge:public Actor {
public:
	Judge(IWorld* world, const std::string& name, const Vector3& position):
		Actor(world,name,position),viewAngle_(30.0f),scoreRate_(1.2f) {
		
	}
	void onUpdate(float deltaTime)override {
		//ターゲットが存在しなければ索敵無効
		if (target_ == nullptr)return;
		//ターゲットの位置を検索
		Vector3 targetPos = target_->position();
		//ターゲット方向のベクトル
		Vector3 toTarget = targetPos - position_;
		//角度を求める
		float forwardAngle = MathHelper::ACos(Vector3::Dot(rotation_.Forward().Normalize(), toTarget.Normalize()));
		float leftAngle = MathHelper::ACos(Vector3::Dot(rotation_.Left().Normalize(), toTarget.Normalize()));

		//視界範囲内だったら
		if (forwardAngle < viewAngle_) {
			//自身を回転させる
			float rotateAngle = 3.0f;
			//左なら右に
			if (leftAngle > 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -rotateAngle);
			//右なら左に
			else if (leftAngle < 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), rotateAngle);

		}

	}
private:
	//視界範囲
	float viewAngle_;
	//スコア上昇率
	float scoreRate_;
};