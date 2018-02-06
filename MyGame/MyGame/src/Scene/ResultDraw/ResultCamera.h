#pragma once
#include"../../Math/Vector3.h"

enum class ResultEasingType {
	Linear,
	EaseOutQuad,
	EaseInCirc
};

class ResultCamera {
public:
	ResultCamera();
	void init();
	void start(const Vector3& nextTarget,const Vector3& add=Vector3::Zero, ResultEasingType xEase = ResultEasingType::Linear, ResultEasingType yEase = ResultEasingType::Linear, ResultEasingType zEase = ResultEasingType::Linear,float speed=1.0f);
	void update(float deltaTime);
	void draw()const;

	void zoomIn();
	void zoomOut();

	bool isEnd()const;

	Vector3 currentTarget()const;

private:
	Vector3 target_{ Vector3::Zero };
	Vector3 nextTarget_{ Vector3::Zero };
	float lerpTimer_;
	float speed_;//çXêVë¨ìx

	Vector3 targetAddVector_{ 0.0f,-30.0f,0.0f };
	Vector3 nextTargetAddVector_{ 0.0f,-30.0f,0.0f };


	ResultEasingType xEase_{ ResultEasingType::Linear };
	ResultEasingType yEase_{ ResultEasingType::Linear };
	ResultEasingType zEase_{ ResultEasingType::Linear };


};