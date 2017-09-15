#pragma once
#include <unordered_map>
#include "../game/ID.h"

class Anime
{
private:
	Anime() = default;
	~Anime() = default;

public:
	static Anime &GetInstance(){
		static Anime a;
		return a;
	}

	///<summary>
	/// �g�p����A�j���[�V�������A�^�b�`����
	///</summary>
	void AttachAnime(const MODEL_ID& id, int animestate);
	///<summary>
	/// �g�p���Ȃ��A�j���[�V��������������
	///</summary>
	void RemoveAnime(const MODEL_ID& id, int animestate);
	///<summary>
	/// �A�j���[�V�����̃t���[�����X�V����
	///</summary>
	void PlayAnime(const MODEL_ID& id, int animestate, float animetime);
	///<summary>
	/// �A�j���[�V�����̑����Ԃ��擾����
	///</summary>
	float GetTotalTime(const MODEL_ID& id, int animestate);
	///<summary>
	/// �������Z�̐ݒ�����Z�b�g����(���A���^�C���������Z�ݒ�̂�)
	///</summary>
	void PhysicsReset(const MODEL_ID& id);
	///<summary>
	/// �������Z���s���i���A���^�C���������Z�ݒ�̂݁j
	///</summary>
	void PhysicsUpdate(const MODEL_ID& id, float time);

	Anime(const Anime& other) = delete;
	Anime& operator = (const Anime& other) = delete;

private:
	std::unordered_map<MODEL_ID, std::unordered_map<int, int>> m_animes;
};