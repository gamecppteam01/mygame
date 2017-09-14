#pragma once

#include <string>
#include <unordered_map>
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../math/Point.h"

class ShadowMap
{
public:
	ShadowMap() = default;
	~ShadowMap();

	///<summary>
	/// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
	///</summary>
	void Set(const std::string& handlename, Point& size);

	///<summary>
	/// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
	///</summary>
	void Set(const std::string& handlename, Point& size, Vector3& lightdirection);

	///<summary>
	/// �V���h�E�}�b�v���폜����
	///</summary>
	void Delete(const std::string& handlename);

	///<summary>
	/// �z�肷�郉�C�g�̕������Z�b�g����
	///</summary>
	void SetLightDirection(const std::string& handlename, const Vector3& lightdirection) const;

	///<summary>
	/// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
	///</summary>
	void SetRange(Vector3& minpos, Vector3& maxpos) const;

	void Enable(int slot) const ;

	void Disable(int slot) const ;

	///<summary>
	/// �V���h�E�}�b�v���J�n����
	///</summary>
	void Begin() const ;

	///<summary>
	/// �V���h�E�}�b�v���I������
	///</summary>
	void End() const ;

private:
	///<summary>
	/// ���Ɏw��̃V���h�E�}�b�v�����݂��Ă�����A�X���[����
	///</summary>
	void AlreadyGrow(const std::string& handlename) const;

	///<summary>
	/// �w��̃V���h�E�}�b�v�����݂��Ă��Ȃ���΁A�X���[����
	///</summary>
	void NoneGrow(const std::string& handlename) const;

	std::unordered_map<std::string, int> m_shadowmaps;// �V���h�E�}�b�v�B���i�[
};