#pragma once
#include "UI.h"
#include "WarningParamter.h"
#include <map>


 enum class warningState {
	UP,
	DOWN,
	RIGHT,
	LEFT,

	None,

};

class WarningManager : public UI {
public:
	//�R���X�g���N�^
	WarningManager();
	//������
	virtual void initialize() override;
	//�X�V
	virtual void update(float deltaTime) override;
	//�`��
	virtual void draw() const override;

	void stateChange(const Vector3& v2);

private:
	std::map<warningState, WarningParamter> parameters_;
	warningState state_;
	
	//�x���̃J�E���g
	int warningCount_;
	//�x���̎���
	float warningTime_;
	
};