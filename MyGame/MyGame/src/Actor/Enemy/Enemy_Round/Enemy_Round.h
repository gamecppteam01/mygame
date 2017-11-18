#pragma once

#include"../BaseEnemy.h"

class Enemy_Round:public BaseEnemy {
	Enemy_Round(IWorld* world, const std::string& name, const Vector3& position, int playerNumber);



};