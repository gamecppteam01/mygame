#pragma once
#include<memory>

class Player;
class SpecifiedStepManager;
class RegulationMaker {
public:
	static void SetRegulation1(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui);
	static void SetRegulation2(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui);
	static void SetRegulation3(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui);
	static void SetRegulationTutorial(const std::shared_ptr<Player>& player, const std::shared_ptr<SpecifiedStepManager>& ui);
};