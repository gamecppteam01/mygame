#pragma once
#include "../Math/Math.h"
#include<list>
#include<map>
#include "../World/IWorld.h"
#include "../Actor/ActorPtr.h"
#include "ScoreRateManager.h"

//�X�R�A���ꊇ�Ǘ��\����
struct ScoreData {
	ScoreData() {

	}
	ScoreData(float rate, int score, int playerNumber, const ActorPtr& target) :
		scoreRate_(rate), score_(score), playerNumber_(playerNumber), target_(target) {

	}
	//�X�R�A�{��
	float scoreRate_;
	//���_
	int score_;
	//�Ώۂ̏o��ԍ�
	int playerNumber_;
	//�Ώ�
	std::weak_ptr<Actor> target_;
};

//�X�R�A�}�l�[�W���[
class ScoreManager {
public:
	//�R���X�g���N�^
	ScoreManager(IWorld* world);
	//�f�X�g���N�^
	~ScoreManager();
	//������
	void initialize();
	//�X�V
	void updata(float deltaTime);
	//�I��̒ǉ�
	void add_Player(int score, int number, float rate ,const ActorPtr& target);
	//�X�R�A�̉��Z
	void addScore(int number, int score);
	//�{���̕ύX
	void ChangeScoreRate(const int number, const float rate);
	//�o�^����Ă���L��������Ԃ�
	int GetCharacterCount()const;
	//�L�����N�^�[�̃X�R�A��Ԃ�
	int GetCharacterScore(int number);
	//�ő�X�R�A��Ԃ�
	int getMaxScore() const;
	//1�ʂ��珇�ɓ�����ScoreData�^�̃��X�g��Ԃ�
	void getRankingList(std::list<ScoreData>& list);

private:
	//���[���h
	IWorld* m_World;
	//�{���Ǘ��N���X
	ScoreRataManager m_RataManager;
	//�X�R�A�f�[�^���X�g
	std::map<int, ScoreData> m_ScoreDataList;
	//�X�R�A���X�g
	std::list<int> m_NumberList;
	//�J�E���g
	int m_Count;
};
