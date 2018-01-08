#include "RegulationMaker.h"
#include"Player.h"

void RegulationMaker::SetRegulation1(const std::shared_ptr<Player>& player)
{
	player->initCheckStep();

	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
	
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});
}

void RegulationMaker::SetRegulation2(const std::shared_ptr<Player>& player)
{
	player->initCheckStep();

	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});

	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
}

void RegulationMaker::SetRegulation3(const std::shared_ptr<Player>& player)
{
	player->initCheckStep();

	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});

	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
}

void RegulationMaker::SetRegulationTutorial(const std::shared_ptr<Player>& player)
{
	player->initCheckStep();

	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});
	player->setCheckStepTask(std::list<Player_Animation>{Player_Animation::Quarter, Player_Animation::Turn});

	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Quarter});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Turn});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Half});
	player->setIncrementStepTask(std::list<Player_Animation>{Player_Animation::Shoot});

}
