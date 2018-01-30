#pragma once
#include "../Math/Vector2.h"
#include <list>
#include "ButtonUIPtr.h"
#include "../Actor/Player/Step_Type.h"
#include "UI.h"

enum class State {
	input,
	output,
};

class ComboGaugeUI : public UI{
public:
	//�R���X�g���N�^
	explicit ComboGaugeUI(const Vector2& gaugePos);
	//������
	virtual void initialize() override;
	//�X�V
	virtual void update(float deltaTime) override;
	//�`��
	virtual void draw() const override;

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