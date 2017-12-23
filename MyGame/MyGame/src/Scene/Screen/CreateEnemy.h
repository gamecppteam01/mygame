#pragma once
#include"../../Actor/Enemy/BaseEnemy.h"
#include"../../Actor/Enemy/Enemy_Notice/Enemy_Notice.h"
#include"../../Actor/Enemy/Enemy_Rival/Enemy_Rival.h"
#include"../../Actor/Enemy/Enemy_Round/Enemy_Round.h"

#include<map>

class IWorld;
class CreateEnemy {
public:
	static void create(IWorld* world, const std::string& filename, int startNumber);//csvファイルを使ってエネミーを生成する(startnumberはプレイヤー番号の開始値)

private:
	static std::map<std::string, std::shared_ptr<BaseEnemy>> enemyList;
};