#include "WorkFolder.h"


std::string WorkFolder::Name = "";

void WorkFolder::SetWorkFolder(std::string foldername)
{
	Name = foldername;
}

// �t�@�C�������o�^����Ă��邩�`�F�b�N����(�P�̊i�[�ϐ�)

// �t�@�C�������o�^����Ă��邩�`�F�b�N����(�����i�[�ϐ�)
void WorkFolder::CheckName(std::string assetname, std::unordered_map<std::string, std::vector<int>> maps)
{
	if (maps.count(assetname) == 0)
	{
		throw std::string(assetname + "�͑��݂��܂���\n");
	}
}