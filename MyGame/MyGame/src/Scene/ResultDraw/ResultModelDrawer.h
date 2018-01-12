#pragma once
#include"../../Graphic/AnimationDx.h"
#include"../../Game/ID.h"

struct Vector3;
struct Matrix;

class ResultModelDrawer {
public:
	ResultModelDrawer();

	void init();
	void setModel(MODEL_ID right,MODEL_ID left);
	void setAnim(int animNum,bool isLoop=false);

	void lastAnim();

	void update(float deltaTime);

	void draw(const Vector3& position,const Matrix& rotation)const;

	bool isEnd()const;
	float getMaxAnimTime()const;
private:
	AnimationDx leftModel_{};
	AnimationDx rightModel_{};

	bool isLoop_{ false };
	int animNum_{ 0 };

};