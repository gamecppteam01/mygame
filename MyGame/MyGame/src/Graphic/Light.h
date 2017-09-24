#pragma once

#include <unordered_map>
#include "../math/Vector3.h"
#include "../math/Color.h"

class Light
{
public:

	///<summary>
	/// �R���X�g���N�^�i�W�����C�g���g�p���邩�ۂ��j
	///</summary>
	Light();
	explicit Light(bool value);
	~Light();

	///<summary>
	/// ����������
	///</summary>
	void Initialize();

	///<summary>
	/// �ʏ탉�C�g���g�p���邩�ۂ�
	///</summary>
	void UseStandardLight(bool value);

	///<summary>
	/// ���C�e�B���O�v�Z�������g�p���邩�ۂ�
	///</summary>
	void UseLighting(bool value);

	///<summary>
	/// �f�B���N�V���i�����C�g���Z�b�g����i�n���h�����A�x�N�g���j
	///</summary>
	void SetDirectionalLight(const std::string& handlename, Vector3& vector);

	///<summary>
	/// �|�C���g���C�g���Z�b�g����i�n���h�����A���W�A�͈́A�����l�O�A�����l�P�A�����l�Q�j
	///</summary>
	void SetPointLight(const std::string& handlename, Vector3& position, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);

	///<summary>
	/// �X�|�b�g���C�g���Z�b�g����i�n���h�����A���W�A�x�N�g���A���C�g�R�[���̊O���̊p�x�A���C�g�R�[���̓����̊p�x�A�͈́A�����l�O�A�����l�P�A�����l�Q�j
	///</summary>
	void SetSpotLight(const std::string& handlename, Vector3& position, Vector3& vector, float cone_outangle, float cone_inangle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);

	///<summary>
	/// �Z�b�g�������C�g����������
	///</summary>
	void DeleteLight(const std::string& handlename);

	///<summary>
	/// ���C�g�̌�����ݒ肷��
	///</summary>
	void SetDirection(const std::string& handlename, Vector3& vector);

	///<summary>
	/// ���C�g�̈ʒu��ݒ肷��
	///</summary>
	void SetPosition(const std::string& handlename, Vector3& position);

	///<summary>
	/// ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
	///</summary>
	void SetDiffuseColor(const std::string& handlename, Color& color);

	///<summary>
	/// ���C�g�̃X�y�L�����[�J���[��ݒ肷��
	///</summary>
	void SetSpecularColor(const std::string& handlename, Color& color);

	///<summary>
	/// ���C�g�̃A���r�G���g�J���[��ݒ肷��
	///</summary>
	void SetAmbientColor(const std::string& handlename, Color& color);

	///<summary>
	/// ���C�g�̃f�B�t���[�Y�J���[���󂯎��
	///</summary>
	Color GetDiffuseColor(const std::string& handlename);

	///<summary>
	/// ���C�g�̃X�y�L�����[�J���[���󂯎��
	///</summary>
	Color GetSpecularColor(const std::string& handlename);

	///<summary>
	/// ���C�g�̃A���r�G���g�J���[���󂯎��
	///</summary>
	Color GetAmbientColor(const std::string& handlename);

	///<summary>
	/// �Z�b�g�������C�g��L���ɂ��邩�����ɂ��邩�ݒ肷��
	///</summary>
	void LightEnable(const std::string& handlename, bool value);

	///<summary>
	/// �Z�b�g����Ă��郉�C�g�̐����擾����
	///</summary>
	int IsLightNumber();

	bool IsEnable(const std::string& name) const;

private:
	///<summary>
	/// ���Ɏw��̃��C�g�����݂��Ă�����A�X���[����
	///</summary>
	void AlreadyGrow(const std::string& handlename);

	///<summary>
	/// �w��̃��C�g�����݂��Ă��Ȃ���΁A�X���[����
	///</summary>
	void NoneGrow(const std::string& handlename);

	std::unordered_map<std::string, int> m_lights;
};