#pragma once

#include "EffekseerForDXLib.h"
#include"../Game/ID.h"
#include<map>

class EffekseerManager {
private:
	EffekseerManager() {
		Initialize();
	}

public:
	static EffekseerManager &GetInstance() {
		static EffekseerManager f;
		return f;
	}
	void Initialize() {
		if (Effkseer_Init(2000) == -1)return;

		// Z�o�b�t�@��L���ɂ���B
		// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
		SetUseZBuffer3D(TRUE);

		// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
		// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
		SetWriteZBuffer3D(TRUE);

		// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
		// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
		// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
		// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
		// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
		Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	}
	//���\�[�X
	void LoadEffect(EFFECT_ID id,const std::string& fileName) {
		effectList_[id] = LoadEffekseerEffect(fileName.c_str());
	}
	void PlayEffect2D(EFFECT_ID id) {
		PlayEffekseer2DEffect(effectList_[id]);
	}
	void PlayEffect3D(EFFECT_ID id) {
		PlayEffekseer3DEffect(effectList_[id]);
	}

	void Update() {
		// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
		Effekseer_Sync3DSetting();
		
		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		UpdateEffekseer3D();

	}
	void Draw()const {
		// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		DrawEffekseer3D();
	}
	void End() {
		effectList_.clear();
		Effkseer_End();
	}

private:
	std::map<EFFECT_ID, int> effectList_;
};