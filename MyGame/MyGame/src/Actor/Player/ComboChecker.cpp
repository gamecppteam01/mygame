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
	bool isDoubleTurn = false;//�^�[��2�A���������̗�O
	for (const auto& parts : comboList) {
		if (parts != Player_Animation::Quarter&&parts != Player_Animation::Turn) {
			isMiss = true;
			break;
		}
		if (i == 2 && parts == Player_Animation::Turn&&comboList.front() == Player_Animation::Turn)isDoubleTurn = true;
		i++;
	}
	//�R���{�p�[�c����Ȃ������������Ă���
	if (isMiss) {
		//����
		comboList.erase(comboList.begin(), comboList.begin() + i);
	}
	if (comboList.size() != 3) {
		if (isDoubleTurn)comboList.pop_back();//�^�[������A����������1�ɂ���
		return ComboChecker::ComboType::Combo_None;//�R���{�͕K��3�A��
	}
	//�|�C���g�A�b�v�̕��т��𒲂ׂ�
	if (std::equal(comboList.begin(), comboList.end(), pointUp.begin(), pointUp.end())) {
		comboList.clear();
		return ComboChecker::ComboType::Combo_PointUp;
	}
	//�o�[�X�g�̕��т��𒲂ׂ�
	if (std::equal(comboList.begin(), comboList.end(), burst.begin(), burst.end())) {
		comboList.clear();
		return ComboChecker::ComboType::Combo_Burst;
	}

	while (!comboList.empty())
	{
		comboList.erase(comboList.begin());
		if (comboList.size() == 1) {
			//�R���{�n���p�[�c���c���Ă��炻��̓L�[�v
			if(comboList.front()==Player_Animation::Quarter|| comboList.front() == Player_Animation::Turn)break;

			//�n���p�[�c����Ȃ�������S�폜
			comboList.clear();
			break;
		}
		else if(comboList.size()==2){
			if (comboList.front() != Player_Animation::Quarter && comboList.front() != Player_Animation::Turn)continue;//�R���{�����������ĂȂ������玟��
			if (comboList.at(1) == Player_Animation::Quarter)break;//2�R���{�����𖞂����Ă��炻�̂܂�

		}
	}
	return ComboChecker::ComboType::Combo_None;
}
