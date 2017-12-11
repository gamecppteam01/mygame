#pragma once
#include <string>
#include "../Math/Vector2.h"

class UI {
public:
	//�R���X�g���N�^
	UI(const std::string& name, const Vector2& position );
	//�f�X�g���N�^
	virtual ~UI(){}
	//�ꎞ��~
	virtual void pause() {};
	//�ĊJ
	virtual void restart() {};
	//������
	virtual void initialize()=0;
	//�X�V
	virtual void update(float deltaTime)=0;
	//�`��
	virtual void draw() const=0;
	
	//���O���擾
	std::string getName()const;

	bool isEnd()const;
protected:
	//�ꏊ
	Vector2 position_;
	//���O
	std::string name_;

	bool isEnd_{ false };
	
};