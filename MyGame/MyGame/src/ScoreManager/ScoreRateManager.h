#pragma once
#include"../World/IWorld.h"
#include<list>
#include"../Actor/Judge/JudgeBase.h"

class ScoreRataManager {
public:
	//�R���X�g���N�^
	ScoreRataManager(IWorld* world);
	//������
	void initialize();
	//�v�Z���ʂ̔{����Ԃ�
	float getRata() const;
	//�R���������񂷂�
	void Judge_Crawl(ActorPtr& target);

private:
	//�R�����̏W�܂�
	void Judge_Group();

private:
	//���[���h
	IWorld*		m_World;
	//�R�����̃O���[�v
	using  s_Judge = std::shared_ptr<JudgeBase>;
	std::list<s_Judge> m_JudgeGroup;
	//�{��
	float m_Rata;
	//�J�E���g
	int m_Count;
};
