#pragma once
#include "../Math/Math.h"
#include<list>
#include<map>
#include "../World/IWorld.h"
#include "../Actor/ActorPtr.h"
#include "ScoreRateManager.h"
#include "ScoreData.h"


//�X�R�A�}�l�[�W���[
class ScoreManager {
public:
	//�R���X�g���N�^
	ScoreManager() = default;
	explicit ScoreManager(IWorld* world);
	//�f�X�g���N�^
	~ScoreManager();
	//������
	void initialize();
	//�X�V
	void updata(float deltaTime);
	//�I��̒ǉ�
	void add_Player(int score, int number, float rate ,int rank ,const ActorPtr& target, MODEL_ID manModel = MODEL_ID::PLAYER_MODEL, MODEL_ID womanModel = MODEL_ID::PLAYER_BULLET_MODEL);
	//�X�R�A�̉��Z
	void addScore(int number, int score);
	//�{���̕ύX
	void ChangeScoreRate(const int number, const float rate);
	//�{���v�Z(�X�|�b�g���C�g�܂�)
	float mathScoreRata_All(const Vector3& target);
	//�{���v�Z(�X�|�b�g���C�g�܂܂Ȃ�)
	float mathScoreRata_All_Not(const Vector3& target);
	//�o�^����Ă���L��������Ԃ�
	int GetCharacterCount()const;
	//�L�����N�^�[�̃X�R�A��Ԃ�
	int GetCharacterScore(int number);
	//�L�����N�^�[�̃X�R�A�{����Ԃ�
	float GetCharacterScoreRate(int number);
	//�ő�X�R�A��Ԃ�
	int getMaxScore() const;
	ScoreData* getScoreData(int num);
	//��ʂ̑I��̃X�R�A�f�[�^��Ԃ�
	ScoreData getFirst();
	//�w��̔{����Ԃ�
	float getRata(const int number) const;
	//list<ScoreData>�^�̃��X�g��n��
	void getScoreDataList(std::list<ScoreData*>& list);
	//
	void getScoreDataMap(std::map<int, ScoreData*> &map);
	//1�ʂ��珇�ɓ�����ScoreData�^�̃��X�g��Ԃ�
	void getRankingList(std::list<ScoreData>& list);
	//�Z���^�[���C�g���ɓ����Ă���I��ԍ��̃��X�g��Ԃ�
	std::list<int> getPlayerNumberList();
	//�X�|�b�g���C�g������������I��̃f�[�^��Ԃ�
	ScoreData* getNoticePlayer();

private:
	//���[���h
	IWorld* m_World;
	//�{���Ǘ��N���X
	ScoreRataManager m_RataManager;
	//�X�R�A�f�[�^���X�g
	std::map<int, ScoreData> m_ScoreDataList;
	//�X�R�A���X�g
	std::list<int> m_NumberList;
	int timeCount_;
	//1�ʂ̑I��f�[�^
	ScoreData m_FirstData;
};
