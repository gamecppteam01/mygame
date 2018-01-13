#pragma once
#include"../Math/Vector3.h"

class Audience {
public:
	Audience();
	void initialize();
	void update(float deltaTime);
	void draw(const Vector3& position,const Vector3& rotation,const int& num) const;
private:
	int count;
	float timer;
};