#include "RegulationMaker.h"
#include"Player.h"
#include"../../UI/SpecifiedStepManager.h"

void RegulationMaker::SetRegulation1(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui)
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

	int num = 1;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 1;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 4;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
}

void RegulationMaker::SetRegulation2(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui)
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

	int num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 1;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 4;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);

}

void RegulationMaker::SetRegulation3(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui)
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

	int num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 4;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 4;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 1;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);

}

void RegulationMaker::SetRegulationTutorial(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui)
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

	int num = 1;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 3;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 2;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);
	num = 4;
	ui->Notify(Notification::Call_ReciveStep, (void*)&num);

}
