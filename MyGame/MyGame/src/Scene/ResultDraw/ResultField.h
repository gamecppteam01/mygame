#pragma once
#include"../../Field/FieldPtr.h"


class ResultField {
public:
	ResultField();

	void init();

	void update(float deltaTime);

	void draw()const;

private:
	FieldPtr field_;
};