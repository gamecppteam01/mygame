#pragma once
#include"../../Graphic/AnimationDx.h"
#include"../../Math/Vector3.h"
#include"../../Math/Math.h"

class ResultAnimation{
public:
	ResultAnimation();
	void initialize();
	void set(const int & handle, const int & handle2);
	void update(float deltaTime);
	void draw(const Vector3& position)const;
	void animation();
	bool end() const;
private:
	AnimationDx animation_;
	AnimationDx animation2_;
	Matrix rotation;
	float timer_;
	
};