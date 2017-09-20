#pragma once
#include <string>
#include "../Math/Vector3.h"

class UI {
public:
	//�R���X�g���N�^
	UI(const std::string& name, const Vector3& position );
	//�f�X�g���N�^
	virtual ~UI(){}

private:
	//������
	virtual void onInitialize();
	//�X�V
	virtual void onUpdate(float deltaTime);
	//�`��
	virtual void onDraw() const;

protected:
	//�ꏊ
	Vector3 _position;
	//���O
	std::string _name;
	
};