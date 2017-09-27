#include "MethodTimer.h"
#include"../math/MathHelper.h"

MethodTimer::MethodTimer() :count_{ 0 }
{
	Initialize();
}

MethodTimer::~MethodTimer()
{
	targetFuncList_.clear();
	emptyCount_.clear();
	MAX_EMPTY_COUNT.clear();
}

void MethodTimer::Initialize()
{
	//���ꂼ��̃��X�g�����������A�l������������
	MAX_EMPTY_COUNT.clear();
	emptyCount_.clear();
	NumReset();
	targetFuncList_.clear();
}

void MethodTimer::InnerInitialize()
{
	//����������
	Initialize();
	//Action�ōs������Z��������
	count_--;
}

void MethodTimer::NumReset()
{
	count_ = 0;
	for (int i = 0; i < (int)emptyCount_.size(); i++) {
		emptyCount_[i] = MAX_EMPTY_COUNT[i];
	}
}

void MethodTimer::AddEmpty(int size)
{
	//�J�E���g��ǉ�����
	MAX_EMPTY_COUNT.push_back(size);
	emptyCount_.push_back(size);

	//���Ԗڂ����v�Z����
	int emptyCount = emptyCount_.size() - 1;
	//���ʗp�̋�̊֐���ǉ�����
	targetFuncList_.push_back([this, emptyCount] {CountEmpty(emptyCount); });
}

void MethodTimer::Add(std::function<void()> func)
{
	targetFuncList_.push_back(func);
}

void MethodTimer::Action()
{
	if ((int)targetFuncList_.size() <= count_)return;

	targetFuncList_[count_]();
	count_++;
}

void MethodTimer::ToLastAction()
{
	if ((int)targetFuncList_.size() <= count_)return;

	count_ = targetFuncList_.size() - 1;

	targetFuncList_[count_]();
	count_++;

}

void MethodTimer::CountEmpty(int count)
{
	if ((int)targetFuncList_.size() <= count_)return;

	//���g�̃J�E���g�����炵��
	emptyCount_[count]--;
	//�J�E���g���I�����ĂȂ�������A�J�E���g���Z�𒠏����ɂ��Ċ֐��𔲂���
	if (emptyCount_[count] > 0) {
		count_--;
		return;
	}

}
