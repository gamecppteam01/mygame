#include "ComboChecker.h"
#include<list>
#include"../../World/IWorld.h"
#include"../../UI/UI.h"
std::vector<Player_Animation> const ComboChecker::pointUp{
	Player_Animation::Quarter,
	Player_Animation::Quarter,
	Player_Animation::Turn
};
std::vector<Player_Animation> const ComboChecker::burst{
	Player_Animation::Turn,
	Player_Animation::Quarter,
	Player_Animation::Turn
};
ComboChecker::ComboType ComboChecker::checkCombo(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld* world) {
	//コンボパーツじゃないのが来たら
	if (next != Player_Animation::Quarter&&next != Player_Animation::Turn) {
		int deleteSize = comboList.size();//削除数
		comboList.clear();
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);
		return ComboType::Combo_None;
	}
	
	switch (comboList.size())
	{
	case 0: {//初コンボなら
		comboList.push_back(next);
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

		return ComboType::Combo_None;
	}
	case 1: {//1コンボしてるなら
		switch (comboList.front())
		{
		case Player_Animation::Quarter: {
			if (next == Player_Animation::Quarter) {
				comboList.push_back(next);
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			}
			else {//次がターンなら
				comboList.clear();
				int deleteSize = 1;//削除数
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

				comboList.push_back(next);
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			}
			break;
		}
		case Player_Animation::Turn: {
			if (next == Player_Animation::Quarter) {
				comboList.push_back(next);
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			}
			else {
				comboList.clear();
				int deleteSize = 1;//削除数
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

				comboList.push_back(next);
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			}

			break;
		}

		default:
			break;
		}
		return ComboType::Combo_None;
	case 2: {//2コンボしてるなら
		if (comboList.front() == Player_Animation::Quarter) {//PUコンボ
			if (next == Player_Animation::Turn) {
				comboList.push_back(next);
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			
				return ComboType::Combo_PointUp;
			}
			else {//クォーターなら
				comboList.erase(comboList.begin());

				int deleteSize = 1;//削除数
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

				comboList.push_back(next);
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

				return ComboType::Combo_None;
			}
		}
		else {//Burstコンボ
			if (next == Player_Animation::Turn) {
				comboList.push_back(next);
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
				return ComboType::Combo_Burst;
			}
			else {//クォーターなら
				comboList.erase(comboList.begin());

				int deleteSize = 1;//削除数
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

				comboList.push_back(next);
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

				return ComboType::Combo_None;
			}

		}
	}
	}
	default:
		comboList.clear();//4個以上だったら全部消す
		break;
	}

	////ポイントアップの並びかを調べる
	//if (std::equal(comboList.begin(), comboList.end(), pointUp.begin(), pointUp.end())) {
	//	comboList.clear();
	//	return ComboChecker::ComboType::Combo_PointUp;
	//}
	////バーストの並びかを調べる
	//if (std::equal(comboList.begin(), comboList.end(), burst.begin(), burst.end())) {
	//	comboList.clear();
	//	return ComboChecker::ComboType::Combo_Burst;
	//}
	//std::list<Player_Animation> saves;
	////ここまで来たらコンボは確実に失敗している

	//int loopsize = comboList.size();

	//for (int i = 0; i < loopsize; i++) {
	//	auto target = comboList.back();
	//	comboList.pop_back();
	//	if (target == Player_Animation::Quarter || target == Player_Animation::Turn) {
	//		saves.push_back(comboList.back());
	//	}

	//}
	//if (comboList.back() == Player_Animation::Quarter || comboList.back() == Player_Animation::Turn) {
	//	saves.push_back(comboList.back());
	//}
	//

	//bool isMiss = false;
	//int i = 1;
	//bool isDoubleTurn = false;//ターン2連続発生時の例外
	//for (const auto& parts : comboList) {
	//	if (parts != Player_Animation::Quarter&&parts != Player_Animation::Turn) {
	//		isMiss = true;
	//		break;
	//	}
	//	if (i == 2 && parts == Player_Animation::Turn&&comboList.front() == Player_Animation::Turn)isDoubleTurn = true;
	//	i++;
	//}
	////コンボパーツじゃない物が混じってたら
	//if (isMiss) {
	//	//消す
	//	comboList.erase(comboList.begin(), comboList.begin() + i);
	//}
	//if (comboList.size() != 3) {
	//	if (isDoubleTurn)comboList.pop_back();//ターンが二連続だったら1つにする
	//	return ComboChecker::ComboType::Combo_None;//コンボは必ず3連式
	//}


	//while (!comboList.empty())
	//{
	//	comboList.erase(comboList.begin());
	//	if (comboList.size() == 1) {
	//		//コンボ始動パーツが残ってたらそれはキープ
	//		if (comboList.front() == Player_Animation::Quarter || comboList.front() == Player_Animation::Turn)break;

	//		//始動パーツじゃなかったら全削除
	//		comboList.clear();
	//		break;
	//	}
	//	else if (comboList.size() == 2) {
	//		if (comboList.front() != Player_Animation::Quarter && comboList.front() != Player_Animation::Turn)continue;//コンボ条件満たしてなかったら次へ
	//		if (comboList.at(1) == Player_Animation::Quarter)break;//2コンボ条件を満たしてたらそのまま

	//	}
	//}
	return ComboChecker::ComboType::Combo_None;
}

ComboChecker::ComboType ComboChecker::checkComboTutorial(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld * world, ComboType type)
{
	if (type == ComboChecker::ComboType::Combo_None) {
		return checkCombo(comboList, next, world);
	}
	//コンボパーツじゃないのが来たら
	if (next != Player_Animation::Quarter&&next != Player_Animation::Turn) {
		int deleteSize = comboList.size();//削除数
		comboList.clear();
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);
		return ComboType::Combo_None;
	}
	switch (type)
	{
	case ComboChecker::ComboType::Combo_PointUp:
		switch (comboList.size())
		{
		case 0: {//初コンボなら
			if (next == Player_Animation::Turn)return ComboType::Combo_None;

			comboList.push_back(next);
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

			return ComboType::Combo_None;
		}
		case 1: {//1コンボしてるなら
			if (next == Player_Animation::Quarter) {
				comboList.push_back(next);
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			}
			else {//次がターンなら
				comboList.clear();
				int deleteSize = 1;//削除数
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

				comboList.push_back(next);
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
			}

			return ComboType::Combo_None;
		}
		case 2: {//2コンボしてるなら
			if (next == Player_Animation::Turn) {
				comboList.push_back(next);
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

				return ComboType::Combo_PointUp;
			}
			else {//クォーターなら
				comboList.erase(comboList.begin());

				int deleteSize = 1;//削除数
				auto stepComboMgr = world->findUI("ComboDrawer");
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

				comboList.push_back(next);
				if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

				return ComboType::Combo_None;
			}

		}
		default:
			comboList.clear();//4個以上だったら全部消す
			break;
		}
		break;
	case ComboChecker::ComboType::Combo_Burst:
		break;
	default:
		break;
	}

	return ComboChecker::ComboType::Combo_None;
}

ComboChecker::ComboType ComboChecker::checkComboBurst(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld * world)
{
	//コンボパーツじゃないのが来たら
	if (next != Player_Animation::Quarter&&next != Player_Animation::Turn) {
		int deleteSize = comboList.size();//削除数
		comboList.clear();
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);
		return ComboType::Combo_None;
	}

	switch (comboList.size())
	{
	case 0: {//初コンボなら
		if (next == Player_Animation::Quarter)return ComboType::Combo_None;

		comboList.push_back(next);
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

		return ComboType::Combo_None;
	}
	case 1: {//1コンボしてるなら
		if (next == Player_Animation::Quarter) {
			comboList.push_back(next);
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
		}
		else {//次がターンなら
			comboList.clear();
			int deleteSize = 1;//削除数
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

			comboList.push_back(next);
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
		}

		return ComboType::Combo_None;
	}
	case 2: {//2コンボしてるなら
		if (next == Player_Animation::Turn) {
			comboList.push_back(next);
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

			return ComboType::Combo_Burst;
		}
		else {//クォーターなら
			comboList.erase(comboList.begin(), comboList.end());

			int deleteSize = 2;//削除数
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

			//comboList.push_back(next);
			//if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

			return ComboType::Combo_None;
		}

	}
	default:
		comboList.clear();//4個以上だったら全部消す
		break;
	}
}

ComboChecker::ComboType ComboChecker::checkComboPointUp(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld * world)
{
	//コンボパーツじゃないのが来たら
	if (next != Player_Animation::Quarter&&next != Player_Animation::Turn) {
		int deleteSize = comboList.size();//削除数
		comboList.clear();
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);
		return ComboType::Combo_None;
	}

	switch (comboList.size())
	{
	case 0: {//初コンボなら
		if (next == Player_Animation::Turn)return ComboType::Combo_None;

		comboList.push_back(next);
		auto stepComboMgr = world->findUI("ComboDrawer");
		if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

		return ComboType::Combo_None;
	}
	case 1: {//1コンボしてるなら
		if (next == Player_Animation::Quarter) {
			comboList.push_back(next);
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);
		}
		else {//次がターンなら
			comboList.clear();
			int deleteSize = 1;//削除数
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);
		}

		return ComboType::Combo_None;
	}
	case 2: {//2コンボしてるなら
		if (next == Player_Animation::Turn) {
			comboList.push_back(next);
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

			return ComboType::Combo_PointUp;
		}
		else {//クォーターなら
			comboList.erase(comboList.begin());

			int deleteSize = 1;//削除数
			auto stepComboMgr = world->findUI("ComboDrawer");
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Delete, (void*)&deleteSize);

			comboList.push_back(next);
			if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_Add, (void*)&next);

			return ComboType::Combo_None;
		}

	}
	default:
		comboList.clear();//4個以上だったら全部消す
		break;
	}
}

ComboChecker::ComboType ComboChecker::checkCombo(std::vector<Player_Animation>& comboList) {
	bool isMiss = false;
	int i = 1;
	bool isDoubleTurn = false;//ターン2連続発生時の例外
	for (const auto& parts : comboList) {
		if (parts != Player_Animation::Quarter&&parts != Player_Animation::Turn) {
			isMiss = true;
			break;
		}
		if (i == 2 && parts == Player_Animation::Turn&&comboList.front() == Player_Animation::Turn)isDoubleTurn = true;
		i++;
	}
	//コンボパーツじゃない物が混じってたら
	if (isMiss) {
		//消す
		comboList.erase(comboList.begin(), comboList.begin() + i);
	}
	if (comboList.size() != 3) {
		if (isDoubleTurn)comboList.pop_back();//ターンが二連続だったら1つにする
		return ComboChecker::ComboType::Combo_None;//コンボは必ず3連式
	}
	//ポイントアップの並びかを調べる
	if (std::equal(comboList.begin(), comboList.end(), pointUp.begin(), pointUp.end())) {
		comboList.clear();
		return ComboChecker::ComboType::Combo_PointUp;
	}
	//バーストの並びかを調べる
	if (std::equal(comboList.begin(), comboList.end(), burst.begin(), burst.end())) {
		comboList.clear();
		return ComboChecker::ComboType::Combo_Burst;
	}

	while (!comboList.empty())
	{
		comboList.erase(comboList.begin());
		if (comboList.size() == 1) {
			//コンボ始動パーツが残ってたらそれはキープ
			if (comboList.front() == Player_Animation::Quarter || comboList.front() == Player_Animation::Turn)break;

			//始動パーツじゃなかったら全削除
			comboList.clear();
			break;
		}
		else if (comboList.size() == 2) {
			if (comboList.front() != Player_Animation::Quarter && comboList.front() != Player_Animation::Turn)continue;//コンボ条件満たしてなかったら次へ
			if (comboList.at(1) == Player_Animation::Quarter)break;//2コンボ条件を満たしてたらそのまま

		}
	}
	return ComboChecker::ComboType::Combo_None;
}

