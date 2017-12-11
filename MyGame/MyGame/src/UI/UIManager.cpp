#include "UIManager.h"
#include"UI.h"
#include<algorithm>

//�R���X�g���N�^
UIManager::UIManager()
{
	initialize();
}

UIManager::~UIManager()
{
	UIs_.clear();
}

void UIManager::pause()
{
	for (auto& u : UIs_) {
		u->pause();
	}
}

void UIManager::restart()
{
	for (auto& u : UIs_) {
		u->restart();
	}
}

//������
void UIManager::initialize()
{
	UIs_.clear();
}

//�X�V
void UIManager::update(float deltaTime)
{
	int size = UIs_.size();
	for (int i = 0; i < size;i++) {
		UIs_.at(i)->update(deltaTime);
	}

	std::vector<UIPtr>::iterator iter = std::remove_if(UIs_.begin(), UIs_.end(), [](UIPtr ui) {return ui->isEnd(); });
	UIs_.erase(iter, UIs_.end());


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
