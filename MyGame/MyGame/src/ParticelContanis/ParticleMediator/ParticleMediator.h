#pragma once

#include<string> 

#include"../ParticlePtr/ParticlePtr.h"

class Particle;

//�p�[�e�B�N������҃N���X
class ParticleMediator {
public:
	//�p�[�e�B�N���𐶐�����
	virtual ParticlePtr generate(const std::string& name) = 0;

protected:
	//�f�X�g���N�^(�C���^�[�t�F�C�X�̃��[�U�[����f�X�g���N�^���֎~)
	~ParticleMediator(){}
};
