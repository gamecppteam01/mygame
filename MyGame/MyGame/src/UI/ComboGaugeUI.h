#pragma once
#include "../Math/Vector2.h"
#include <list>
#include "ButtonUIPtr.h"
#include "../Actor/Player/Step_Type.h"

enum class State {
	input,
	output,
};

class ComboGaugeUI {
public:
	//�R���X�g���N�^
	ComboGaugeUI(const Vector2& gaugePos);
	//�J�n
	void start();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw() const;

private:
	//�{�^������
	void createButton(const Step_Type& type);
	//
	void stateUpdete(float deltaTime);
	//
	void inputUpdate(float deltaTime);
	//
	void outputUpdate(float deltaTime);

private:
	//�Q�[�W
	Vector2 gaugePos_;
	//�Q�[�W�̉���
	RECT gaugeRect_;
	//�Q�[�W�̉���
	float gaugeWidth_;
	//���݂̎���
	float nowTime_;
	//�ő厞��
	float maxTime_;
	//�{�^������
	int ButtonCount_;
	//
	int t;
	//
	State state_;
	//�{�^���|�C���^�[
	std::list<ButtonUIPtr> buttonList_;
};