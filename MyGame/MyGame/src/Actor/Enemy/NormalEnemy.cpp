#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	BaseEnemy(world,name,position,playerNumber_,body){

}
