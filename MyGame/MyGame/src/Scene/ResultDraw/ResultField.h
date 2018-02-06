#pragma once
#include"../../Field/FieldPtr.h"


class ResultField {
public:
	ResultField();

	void init();

	void update(float deltaTime);

	void draw()const;

	void setBright(float r, float g, float b);
private:
	FieldPtr field_;
};