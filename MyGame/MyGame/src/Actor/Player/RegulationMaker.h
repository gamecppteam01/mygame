#pragma once
#include<memory>

class Player;
class RegulationMaker {
public:
	static void SetRegulation1(const std::shared_ptr<Player>& player);
	static void SetRegulation2(const std::shared_ptr<Player>& player);
	static void SetRegulation3(const std::shared_ptr<Player>& player);
	static void SetRegulationTutorial(const std::shared_ptr<Player>& player);
};