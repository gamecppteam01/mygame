#include "EffekseerManager.h"
#include "EffekseerManager.h"
#include "EffekseerManager.h"

EffekseerManager::EffekseerManager()
{
	Initialize();
}

EffekseerManager::~EffekseerManager()
{
	trackEffectList_.clear();
}

void EffekseerManager::Initialize()
{
	if (Effkseer_Init(2000) == -1)return;
	handle_ = 0;

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

void EffekseerManager::LoadEffect(EFFECT_ID id, const std::string & fileName)
{
	effectList_[id] = LoadEffekseerEffect(fileName.c_str());
}

int EffekseerManager::PlayEffect2D(EFFECT_ID id, Vector3 position, Vector3 rotation, Vector3 scale)
{
	handle_ = PlayEffekseer2DEffect(effectList_[id]);
	SetScalePlayEffect2D(handle_, scale);
	SetRotateEffect2D(handle_, scale);
	SetPosPlayEffect2D(handle_, scale);
	return handle_;
}

int EffekseerManager::PlayEffect3D(EFFECT_ID id, Vector3 position, Vector3 rotation, Vector3 scale)
{
	handle_ = PlayEffekseer3DEffect(effectList_[id]);
	SetScalePlayEffect3D(handle_, scale);
	SetRotateEffect3D(handle_, rotation);
	SetPosPlayEffect3D(handle_, position);
	return handle_;
}

bool EffekseerManager::isPlayEffect3D(int id)
{
	return IsEffekseer3DEffectPlaying(id) == 0;
}

void EffekseerManager::StopEffect3D(int id)
{
	int a = StopEffekseer3DEffect(id);
}

void EffekseerManager::SetPositionTrackTarget(EFFECT_ID effectid, int handle, Vector3 * position)
{
	trackEffectList_.push_back(std::make_tuple(effectid, handle, position));
}

int EffekseerManager::SetPosPlayEffect3D(int handle, Vector3 position)
{
	return SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);
}

int EffekseerManager::SetPosPlayEffect2D(int handle, Vector3 position)
{
	return SetPosPlayingEffekseer2DEffect(handle, position.x, position.y, position.z);
}

int EffekseerManager::SetRotateEffect3D(int handle, Vector3 rotation)
{
	return SetRotationPlayingEffekseer3DEffect(handle, rotation.x, rotation.y, rotation.z);
}

int EffekseerManager::SetRotateEffect2D(int handle, Vector3 rotation)
{
	return SetRotationPlayingEffekseer3DEffect(handle, rotation.x, rotation.y, rotation.z);
}

int EffekseerManager::SetScalePlayEffect3D(int handle, Vector3 scale)
{
	return SetScalePlayingEffekseer3DEffect(handle, scale.x, scale.y, scale.z);
}

int EffekseerManager::SetScalePlayEffect2D(int handle, Vector3 scale)
{
	return SetScalePlayingEffekseer2DEffect(handle, scale.x, scale.y, scale.z);
}

void EffekseerManager::Update()
{
	if (IsStopFlg_) return;
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	trackEffectList_.remove_if([&](std::tuple<EFFECT_ID, int, Vector3*>& target) {
		int key = std::get<1>(target);
		return IsEffekseer3DEffectPlaying(key)==-1;
	});

	for (auto& tel : trackEffectList_) {
		if (std::get<2>(tel) == nullptr)continue;

		SetPosPlayEffect3D(std::get<1>(tel), *std::get<2>(tel));
	}

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();
}

void EffekseerManager::Draw() const
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}

void EffekseerManager::End()
{
	effectList_.clear();
	Effkseer_End();
}

