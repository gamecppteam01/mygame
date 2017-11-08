#pragma once
#include <vector>
#include "UI.h"
#include "UIPtr.h"

//UI�`����Ǘ�����N���X
class UIManager {
public:
	//�R���X�g���N�^
	UIManager();
	~UIManager();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw() const;
	//����
	UIPtr find(const std::string& name);
	//�ǉ�
	void add(const UIPtr& uiptr);

private:
	
	std::vector<UIPtr> UIs_;
};