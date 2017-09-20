#pragma once
#include <vector>
#include "UI.h"
#include "UIPtr.h"

class UIManager {
public:
	//�R���X�g���N�^
	UIManager();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw() const;
	//����
	void find(const std::string& name);
	//�ǉ�
	void add(const UIPtr& uiptr);

private:
	
	std::vector<UIPtr> UIs_;
};