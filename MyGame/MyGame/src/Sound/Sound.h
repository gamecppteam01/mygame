#pragma once

#include <Dxlib.h>
#include <array>
#include <string>
#include <unordered_map>
#include "../game/ID.h"

class Sound
{
private:
	Sound();
	~Sound();

public:
	static Sound &GetInstance() {
		static Sound s;
		return s;
	}

	///<summary>
	/// ����������
	///</summary>
	void Initialize();

	///<summary>
	/// BGM��ǂݍ���
	///</summary>
	void LoadBGM(const std::string& filename, const BGM_ID& id, float volume = 1.0f);
	///<summary>
	/// SE��ǂݍ���
	///</summary>
	void LoadSE(const std::string& filename, const SE_ID& id, float volume = 1.0f);
	///<summary>
	/// 3D(���̉���)�ōĐ�������SE��ǂݍ���
	///</summary>
	void Load3DSE(const std::string& filename, const SE_ID& id, float volume = 1.0f);

	///<summary>
	/// �ǂݍ���BGM�ASE�����ׂč폜����
	///</summary>
	void DeleteAll();
	///<summary>
	/// BGM��炷
	///</summary>
	void PlayBGM(const BGM_ID& id, int playtype = DX_PLAYTYPE_BACK);
	///<summary>
	/// SE��炷
	///</summary>
	void PlaySE(const SE_ID& id, int playtype = DX_PLAYTYPE_BACK);
	///<summary>
	/// ����SE���d�Ȃ�Ȃ��悤�ɖ炷
	///</summary>
	void PlaySEDuplicate(const SE_ID& id, int playtype = DX_PLAYTYPE_BACK);
	///<summary>
	/// BGM���~�߂�
	///</summary>
	void StopBGM();
	///<summary>
	/// SE���~�߂�
	///</summary>
	void StopSE(const SE_ID& id);
	void StopSE();

	///<summary>
	/// BGM�����Ă��邩�ǂ������ׂ�
	///</summary>
	bool IsPlayBGM();
	///<summary>
	/// SE�����Ă��邩�ǂ������ׂ�
	///</summary>
	bool IsPlaySE(const SE_ID& id);

	///<summary>
	/// �eBGM�̃{�����[����ݒ肷��
	///</summary>
	void SetBGMVolume(const BGM_ID& id, float volume);
	///<summary>
	/// �eSE�̃{�����[����ݒ肷��
	///</summary>
	void SetSEVolume(const SE_ID& id, float volume);
	///<summary>
	/// �eBGM�̃{�����[�����󂯎��
	///</summary>
	float IsBGMVolume(const BGM_ID& id);
	///<summary>
	/// �eSE�̃{�����[�����󂯎��
	///</summary>
	float IsSEVolume(const SE_ID& id);

	///<summary>
	/// �S�Ă�BGM�̃{�����[����ݒ肷��
	///</summary>
	void SetAllBGMVolume(float volume);
	///<summary>
	/// �S�Ă�SE�̃{�����[����ݒ肷��
	///</summary>
	void SetAllSEVolume(float volume);
	///<summary>
	/// �S�Ă�BGM�̃{�����[�����󂯎��
	///</summary>
	float IsAllBGMVolume();
	///<summary>
	/// �S�Ă�SE�̃{�����[�����󂯎��
	///</summary>
	float IsAllSEVolume();

	int GetCountBGM()
	{
		return static_cast<int>(m_BGMs.size());
	}
	int GetCountSE()
	{
		return static_cast<int>(m_SEs.size());
	}

	void Update();

	Sound(const Sound& other);
	Sound& operator = (const Sound& other);

private:
	std::string Split(const std::string& filename);

private:
	void SettingBGM(const BGM_ID& id);

	void SettingSE(const SE_ID& id);

	std::unordered_map<BGM_ID, int> m_BGMs;				// BGM�n���h��
	std::unordered_map<SE_ID, int> m_SEs;				// SE�n���h��
	std::unordered_map<BGM_ID, float> m_BGM_Volumes;	// �eBGM�{�����[��
	std::unordered_map<SE_ID, float> m_SE_Volumes;		// �eSE�{�����[��
	float m_bgm_volume;									// �SBGM�{�����[��
	float m_se_volume;									// �SSE�{�����[��

	std::array<int, 512>				dupSE;			// �����Đ��\SE
};