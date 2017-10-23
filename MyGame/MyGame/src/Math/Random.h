#pragma once

#include <random>

class Random
{
private:
	Random();
	explicit Random(int seed);
	~Random() = default;

public:
	static Random &GetInstance(){
		static Random m;
		return m;
	}

	///<summary>
	/// �V�[�h���Z�b�g����
	///</summary>
	void SetSeed(int seed);

	///<summary>
	/// �����^�̗����𐶐�����i�ŏ��l�A�ő�l�j
	///</summary>
	int Range(int min, int max);

	///<summary>
	/// �����^�̗����𐶐�����i�ŏ��l�A�ő�l�j
	///</summary>
	float Range(float min, float max);

	///<summary>
	/// �N�_�l�̗����𐶐�����i�N�_�l�A���U�l�j
	///</summary>
	float Point(float point, float variance);

	template <class T>
	T Randomize(const std::vector<T>& list);
private:
	std::random_device	m_rnd_dev;	// �����V�[�h
	std::mt19937		m_mt;			// ����������
};

template<class T>
T Random::Randomize(const std::vector<T>& list)
{
	int target = Range(0, list.size()-1);
	return list[target];

}
