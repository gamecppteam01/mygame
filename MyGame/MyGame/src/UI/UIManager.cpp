#include "UIManager.h"
#include"UI.h"

//�R���X�g���N�^
UIManager::UIManager()
{
	initialize();
}

UIManager::~UIManager()
{
	UIs_.clear();
}

//������
void UIManager::initialize()
{
	UIs_.clear();
}

//�X�V
void UIManager::update(float deltaTime)
{
	for (auto& ui : UIs_) {
		ui->update(deltaTime);
	}
}

//�`��
void UIManager::draw() const
{
	for (auto& ui : UIs_) {
		ui->draw();
	}
}

//����
UIPtr UIManager::find(const std::string & name)
{
	//���O����v����v�f�����݂���΂����return
	for (auto& ui : UIs_) {
		if (ui->getName()==name)return ui;
	}
	//���Ȃ�������null��return
	return nullptr;
}

//�ǉ�
void UIManager::add(const UIPtr & uiptr)
{
	UIs_.push_back(uiptr);
	uiptr->initialize();
}
