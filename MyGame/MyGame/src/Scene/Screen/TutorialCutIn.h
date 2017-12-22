#pragma once
#include"../../Game/ID.h"

class TutorialCutIn {
public:
	static void draw(SPRITE_ID id, float yPos, float time, float stopTime = 0.5f, float inTime = 1.0f, float outTime = 1.0f);
};