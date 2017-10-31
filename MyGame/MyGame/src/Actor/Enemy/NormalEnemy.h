#pragma once
#include"BaseEnemy.h"

class NormalEnemy :public BaseEnemy {
public:
	NormalEnemy(IWorld* world,const std::string& name,const Vector3& position,const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	
};