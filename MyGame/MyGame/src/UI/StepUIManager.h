#pragma once
#include"UI.h"
#include"../Actor/Player/Player.h"
#include"StepUIPtr.h"
#include"StepUI.h"
#include"../Graphic/FontManager.h"
#include"../World/World.h"
#include<memory>

class StepUIManager : public UI {
public:
	StepUIManager(IWorld* world);
	//������
	void initialize() override;
	//�X�V
	void update(float deltaTime)override;
	//�`��
	void draw()const override;
	//�X�e�b�v�������ۂ�
	bool is_StepSuccess() const;
private:
	IWorld* world_;
	std::weak_ptr<Player> player_;
};