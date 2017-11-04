#pragma once

#include "EffekseerForDXLib.h"
#include"../Game/ID.h"
#include"../Math/Math.h"
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

		IsStopFlg_ = false;
	}

	//���\�[�X
	void LoadEffect(EFFECT_ID id,const std::string& fileName) {
		effectList_[id] = LoadEffekseerEffect(fileName.c_str());
	}
	//�Đ�
	int PlayEffect2D(EFFECT_ID id, Vector3 position = Vector3::Zero, Vector3 rotation = Vector3::Zero, Vector3 scale = Vector3::One) {
		int handle = PlayEffekseer2DEffect(effectList_[id]);
		SetScalePlayEffect2D(handle, scale);
		SetRotateEffect2D(handle, scale);
		SetPosPlayEffect2D(handle, scale);
		return handle;
	}
	int PlayEffect3D(EFFECT_ID id, Vector3 position = Vector3::Zero, Vector3 rotation = Vector3::Zero, Vector3 scale = Vector3::One) {
		int handle = PlayEffekseer3DEffect(effectList_[id]);
		SetScalePlayEffect3D(handle, scale);
		SetRotateEffect3D(handle, rotation);
		SetPosPlayEffect3D(handle, position);
		return handle;
	}
	
	//�ꏊ
	int SetPosPlayEffect3D(int handle, Vector3 position) {
		return SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);
	}
	int SetPosPlayEffect2D(int handle, Vector3 position) {
		return SetPosPlayingEffekseer2DEffect(handle, position.x, position.y , position.z);
	}
	//��]
	int SetRotateEffect3D(int handle, Vector3 rotation) {
		return SetRotationPlayingEffekseer3DEffect(handle, rotation.x, rotation.y, rotation.z);
	}
	int SetRotateEffect2D(int handle, Vector3 rotation) {
		return SetRotationPlayingEffekseer3DEffect(handle, rotation.x, rotation.y, rotation.z);
	}
	//�g��
	int SetScalePlayEffect3D(int handle, Vector3 scale) {
		return SetScalePlayingEffekseer3DEffect(handle, scale.x, scale.y, scale.z);
	}
	int SetScalePlayEffect2D(int handle, Vector3 scale) {
		return SetScalePlayingEffekseer2DEffect(handle, scale.x, scale.y, scale.z);
	}


	void Update() {
		if (IsStopFlg_) return;
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
	bool IsStopFlg_;
};