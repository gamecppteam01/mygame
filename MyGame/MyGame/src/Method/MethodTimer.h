#pragma once
#include<functional>
#include<vector>

class MethodTimer {
public:
	//�o�^�����֐������ԂɌĂяo���N���X
	MethodTimer();
	~MethodTimer();

	//�o�^����Ă���֐���S�č폜���A�J�E���g��0�ɂ���
	void Initialize();

	//Action�֐�����Initialize����ꍇ�͍���
	void InnerInitialize();
	//�J�E���g��0�ɂ���
	void NumReset();
	//��̊֐���ǉ�����
	void AddEmpty(int size);
	//�֐���ǉ��o�^����
	void Add(std::function<void()> func);
	//�o�^���ꂽ�֐������s����A�J�E���g���ő�l�𒴂�����A����������return����
	void Action();
	//�o�^���ꂽ�ő�l�̃J�E���g�Ɉړ����A�֐������s����
	void ToLastAction();
private:
	//��̊֐������J�E���g��i�߂�
	void CountEmpty(int count);

private:
	//�Ăяo���񐔃J�E���^
	int count_;

	//��̌Ăяo���񐔃��X�g
	std::vector<int> emptyCount_;
	std::vector<int> MAX_EMPTY_COUNT;

	//�֐����X�g
	std::vector<std::function<void()>> targetFuncList_;
};