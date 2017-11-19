#include "Enemy_Round.h"

Enemy_Round::Enemy_Round(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber):
	BaseEnemy(world,name,position,playerNumber)
{

}

void Enemy_Round::to_Normal()
{
}

void Enemy_Round::updateNormal(float deltaTime)
{
}
