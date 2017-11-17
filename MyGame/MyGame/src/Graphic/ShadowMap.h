#pragma once

#include <string>
#include <unordered_map>
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../Game/ID.h"

class ShadowMap
{
public:
	ShadowMap() = default;
	~ShadowMap();

	///<summary>
	/// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
	///</summary>
	void Set(const SHADOW_MAP_ID& id, const Point& size);

	///<summary>
	/// �V���h�E�}�b�v���Z�b�g����i���C�g�̐ݒ�܂�,size��2��n��Őݒ肷��j
	///</summary>
	void Set(const SHADOW_MAP_ID& id, const Point& size, Vector3& lightdirection);

	///<summary>
	/// �V���h�E�}�b�v���폜����
	///</summary>
	void Delete(const SHADOW_MAP_ID& id);

	void Clear();

	///<summary>
	/// �z�肷�郉�C�g�̕������Z�b�g����
	///</summary>
	void SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& lightdirection) const;

	///<summary>
	/// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
	///</summary>
	void SetRange(Vector3& minpos, Vector3& maxpos) const;

	void Enable(int slot) const ;
	//�w�肵���V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
	void Enable(const SHADOW_MAP_ID& id, int slot) const;

	void Disable(int slot) const ;
	
	///<summary>
	/// �V���h�E�}�b�v���J�n����
	///</summary>
	void Begin() const ;

	///<summary>
	/// �w�肵���V���h�E�}�b�v���J�n����
	///</summary>
	void Begin(const SHADOW_MAP_ID& id) const;

	///<summary>
	/// �V���h�E�}�b�v���I������
	///</summary>
	void End() const ;
	
private:
	///<summary>
	/// ���Ɏw��̃V���h�E�}�b�v�����݂��Ă�����A�X���[����
	///</summary>
	void AlreadyGrow(const SHADOW_MAP_ID& id) const;

	///<summary>
	/// �w��̃V���h�E�}�b�v�����݂��Ă��Ȃ���΁A�X���[����
	///</summary>
	void NoneGrow(const SHADOW_MAP_ID& id) const;

	std::unordered_map<SHADOW_MAP_ID, int> m_shadowmaps;// �V���h�E�}�b�v�B���i�[

public:
	static const Point RESOLUTION_1024;
	static const Point RESOLUTION_2048;
	static const Point RESOLUTION_4096;
	static const Point RESOLUTION_8192;
	static const Point RESOLUTION_16384;
};