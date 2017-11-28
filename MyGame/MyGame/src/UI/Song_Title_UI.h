#pragma once

#include"UI.h"
#include<map>
#include<string>

class Song_Title_UI : public UI {
public:
	//�R���X�g���N�^
	Song_Title_UI(int soundhandle);
	//������
	virtual void initialize() override;
	//�X�V
	virtual void update(float deltaTime) override;
	//�`��
	virtual void draw() const override;

private:
	void createSongList();

private:
	//�Ȗ����X�g
	std::map<int, std::string> songMap_;
	//�ȃn���h��
	int soundhandle_;
};
