#pragma once
#include<utility>

namespace DualshockKey {

	const std::pair<int, int> Circle = std::make_pair(5, 0b1000000);
	const std::pair<int, int> Cross = std::make_pair(5, 0b100000);
	const std::pair<int, int> Square = std::make_pair(5, 0b10000);
	const std::pair<int, int> Triangle = std::make_pair(5, 0b10000000);

	const std::pair<int, int> R1 = std::make_pair(6, 0b10);
	const std::pair<int, int> L1 = std::make_pair(6, 0b1);
	const std::pair<int, int> R2 = std::make_pair(6, 0b1000);
	const std::pair<int, int> L2 = std::make_pair(6, 0b100);
	const std::pair<int, int> Option = std::make_pair(6, 0b100000);
	const std::pair<int, int> Share = std::make_pair(6, 0b10000);


};
