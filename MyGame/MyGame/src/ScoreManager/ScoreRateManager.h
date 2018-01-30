#pragma once
#include"../World/IWorld.h"
#include<list>
#include"../Actor/Judge/JudgeBase.h"

class ScoreRataManager {
public:
	//�R���X�g���N�^
	explicit ScoreRataManager(IWorld* world);
	//������
	void initialize();
	//�v�Z���ʂ̔{����Ԃ�
	float getRata() const;
	//�R���������񂷂�
	void Judge_Crawl(ActorPtr& target);
	//�{���v�Z(�X�|�b�g���C�g�܂�)
	float mathScoreRata_All(const Vector3& target);
	//�{���v�Z(�X�|�b�g���C�g�܂܂Ȃ�)
	float mathScoreRata_All_Not(const Vector3& target);

private:
	//�R�����̏W�܂�
	void Judge_Collect();

private:
	//���[���h
	IWorld*		m_World;
	//�R�����̃O���[�v
	using  s_Judge = std::shared_ptr<JudgeBase>;
	std::list<s_Judge> m_JudgeAll;		//�X�|�b�g���C�g�܂�
	std::list<s_Judge> m_JudgeAll_Not;		//�X�|�b�g���C�g�܂܂Ȃ�
	//�{��
	float m_Rata;
	//�J�E���g
	int m_Count;
};
