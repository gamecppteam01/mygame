#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class WorkFolder
{
public:
	///<summary>
	/// �t�@�C�����i�[����Ă���t�H���_�[����ݒ肷��
	///</summary>
	static void SetWorkFolder(std::string foldername);

	///<summary>
	/// �t�@�C�������o�^����Ă��邩�`�F�b�N����(�P�̊i�[�ϐ�)
	///</summary>
	template <typename T>
	static void CheckName(std::string assetname,  const std::unordered_map<std::string, T>& maps)
	{
		if (maps.count(assetname) == 0)
		{
			throw std::string(assetname + "�͑��݂��܂���\n");
		}
	}

	///<summary>
	/// �t�@�C�������o�^����Ă��邩�`�F�b�N����(�����i�[�ϐ�)
	///</summary>
	static void CheckName(std::string assetname, std::unordered_map<std::string, std::vector<int>> maps);

	static std::string Name;
};