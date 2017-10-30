#pragma once
#include"../Math/Vector3.h"
#include"../Math/TwoDimensionalArray.h"
#include"../Method/MethodTimer.h"
#include<memory>
#include<vector>

class IWorld;
class Judge_NPC;

class ScoreMap {
private:

public:
	//�X�R�A�{�������|�C���g
	struct ScorePoint
	{
		ScorePoint(Vector3 position = Vector3::Zero,float rate = 1.0f) :rate_(rate), position_(position) {
		}

		float rate_;
		Vector3 position_;
	};
public:
	explicit ScoreMap(IWorld* world);
	~ScoreMap();
	void initialize();
	//���쐬
	void update(float deltaTime);
	//���͂̃|�C���g�ň�ԃX�R�A�{���̍�������Ԃ�
	Vector3 getNextPoint(const Vector3& point);

private:
	//�{������
	void mathScoreRate();

private:
	IWorld* world_;
	//�X�R�A���[�g�v�Z�^�C�}�[
	MethodTimer mathScoreRateTimer_;
	//�X�R�A�ʒu��
	TwoDimensionalArray<ScorePoint> points_{
		4,4,
		ScorePoint{ Vector3(-120.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,-120.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,-120.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,-40.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,-40.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,40.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,40.0f) },
		ScorePoint{ Vector3(-120.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(-40.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(40.0f,0.0f,120.0f) }	,ScorePoint{ Vector3(-120.0f,0.0f,120.0f) }
	};
	//�R�������X�g
	std::vector<std::shared_ptr<Judge_NPC>> judges_;

};