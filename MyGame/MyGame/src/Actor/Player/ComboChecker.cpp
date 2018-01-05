#include "ComboChecker.h"

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
ComboChecker::ComboType ComboChecker::checkCombo(std::vector<Player_Animation>& comboList) {
	bool isMiss = false;
	int i = 1;
	for (const auto& parts : comboList) {
		if (parts != Player_Animation::Quarter&&parts != Player_Animation::Turn) {
			isMiss = true;
			break;
		}
		i++;
	}
	//コンボパーツじゃない物が混じってたら
	if (isMiss) {
		//消す
		comboList.erase(comboList.begin(), comboList.begin() + i);
	}
	if (comboList.size() != 3)return ComboChecker::ComboType::Combo_None;//コンボは必ず3連式

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
			if(comboList.front()==Player_Animation::Quarter|| comboList.front() == Player_Animation::Turn)break;

			//始動パーツじゃなかったら全削除
			comboList.clear();
			break;
		}
		else if(comboList.size()==2){
			if (comboList.front() != Player_Animation::Quarter && comboList.front() != Player_Animation::Turn)continue;//コンボ条件満たしてなかったら次へ
			if (comboList.at(1) == Player_Animation::Quarter)break;//2コンボ条件を満たしてたらそのまま

		}
	}
	return ComboChecker::ComboType::Combo_None;
}
