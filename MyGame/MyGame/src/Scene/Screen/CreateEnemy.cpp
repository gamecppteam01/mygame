#include "CreateEnemy.h"
#include"../../Resource/CsvReader.h"
#include"../../Math/Vector3.h"
#include"../../World/IWorld.h"
#include"../../Actor/ActorGroup.h"


std::map<std::string, std::shared_ptr<BaseEnemy>> CreateEnemy::enemyList = {
	{ "Round", std::make_shared<Enemy_Round>() },
	{ "Rival",std::make_shared<Enemy_Rival>() },
	{ "Notice",std::make_shared<Enemy_Notice>() }
};

void CreateEnemy::create(IWorld * world, const std::string & filename,int startNumber)
{
	CsvReader cr{ filename };

	std::string typeName;
	Vector3 position;
	int playerNumber = startNumber;
	for (int i = 0; i < cr.rows(); i++) {
		typeName = cr.get(i, 0);
		position = { cr.getf(i, 1),cr.getf(i, 2),cr.getf(i, 3) };

		//エネミーの追加
		world->addActor(ActorGroup::ENEMY, enemyList.at(typeName)->Create(world, position, playerNumber));
	
		playerNumber++;
	}
}
