#include "Light.h"
#include "../math/MathHelper.h"
#include <Dxlib.h>

// �R���X�g���N�^�i�W�����C�g���g�p���邩�ۂ��j
Light::Light()
	: Light(false) {}
Light::Light(bool value)
{
	SetLightEnable(value);
	m_lights.clear();
}

Light::~Light()
{
	DeleteLightHandleAll();
}

// ����������
void Light::Initialize()
{
	for (auto& i : m_lights)
	{
		DeleteLight(i.first);
	}
}

// �ʏ탉�C�g���g�p���邩�ۂ�
void Light::UseStandardLight(bool value)
{
	SetLightEnable(value);
}

///<summary>
/// ���C�e�B���O�v�Z�������g�p���邩�ۂ�
///</summary>
void Light::UseLighting(bool value)
{
	SetUseLighting(value);
}

// �f�B���N�V���i�����C�g���Z�b�g����i�n���h�����A�x�N�g���j
void Light::SetDirectionalLight(const std::string& handlename, Vector3& vector)
{
	AlreadyGrow(handlename);
	m_lights[handlename] = CreateDirLightHandle(VGet(vector.x, vector.y, vector.z));
}

// �|�C���g���C�g���Z�b�g����i�n���h�����A���W�A�͈́A�����l�O�A�����l�P�A�����l�Q�j
void Light::SetPointLight(const std::string& handlename, Vector3& position, float range, float atten0, float atten1, float atten2)
{
	AlreadyGrow(handlename);
	m_lights[handlename] = CreatePointLightHandle(VGet(position.x, position.y, position.z), range, atten0, atten1, atten2);
}

// �X�|�b�g���C�g���Z�b�g����i�n���h�����A���W�A�x�N�g���A���C�g�R�[���̊O���̊p�x�A���C�g�R�[���̓����̊p�x�A�͈́A�����l�O�A�����l�P�A�����l�Q�j
void Light::SetSpotLight(const std::string& handlename, Vector3& position, Vector3& vector, float cone_outangle, float cone_inangle, float range, float atten0, float atten1, float atten2)
{
	AlreadyGrow(handlename);
	m_lights[handlename] = CreateSpotLightHandle(VGet(position.x, position.y, position.z), VGet(vector.x, vector.y, vector.z),
		MathHelper::ToRadians(cone_outangle), MathHelper::ToRadians(cone_inangle), range, atten0, atten1, atten2);
}

// �Z�b�g�������C�g����������
void Light::DeleteLight(const std::string& handlename)
{
	NoneGrow(handlename);
	DeleteLightHandle(m_lights[handlename]);
	m_lights.erase(handlename);
}

// ���C�g�̌�����ݒ肷��
void Light::SetDirection(const std::string& handlename, Vector3& vector)
{
	NoneGrow(handlename);
	SetLightDirectionHandle(m_lights[handlename], VGet(vector.x, vector.y, vector.z));
}

// ���C�g�̈ʒu��ݒ肷��
void Light::SetPosition(const std::string& handlename, Vector3& position)
{
	NoneGrow(handlename);
	SetLightPositionHandle(m_lights[handlename], VGet(position.x, position.y, position.z));
}

// ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
void Light::SetDiffuseColor(const std::string& handlename, Color& color)
{
	NoneGrow(handlename);
	color *= 255.0f;
	SetLightDifColorHandle(m_lights[handlename], GetColorF(color.r, color.g, color.b, color.a));
}

// ���C�g�̃X�y�L�����[�J���[��ݒ肷��
void Light::SetSpecularColor(const std::string& handlename, Color& color)
{
	NoneGrow(handlename);
	color *= 255.0f;
	SetLightSpcColorHandle(m_lights[handlename], GetColorF(color.r, color.g, color.b, color.a));
}

// ���C�g�̃A���r�G���g�J���[��ݒ肷��
void Light::SetAmbientColor(const std::string& handlename, Color& color)
{
	NoneGrow(handlename);
	color *= 255.0f;
	SetLightAmbColorHandle(m_lights[handlename], GetColorF(color.r, color.g, color.b, color.a));
}

// ���C�g�̃f�B�t���[�Y�J���[���󂯎��
Color Light::GetDiffuseColor(const std::string& handlename)
{
	COLOR_F lib_color = GetLightDifColorHandle(m_lights[handlename]);
	return Color(lib_color.r / 255.0f, lib_color.g / 255.0f, lib_color.b / 255.0f, lib_color.a / 255.0f);
}

// ���C�g�̃X�y�L�����[�J���[���󂯎��
Color Light::GetSpecularColor(const std::string& handlename)
{
	COLOR_F lib_color = GetLightSpcColorHandle(m_lights[handlename]);
	return Color(lib_color.r / 255.0f, lib_color.g / 255.0f, lib_color.b / 255.0f, lib_color.a / 255.0f);
}

// ���C�g�̃A���r�G���g�J���[���󂯎��
Color Light::GetAmbientColor(const std::string& handlename)
{
	COLOR_F lib_color = GetLightAmbColorHandle(m_lights[handlename]);
	return Color(lib_color.r / 255.0f, lib_color.g / 255.0f, lib_color.b / 255.0f, lib_color.a / 255.0f);
}

// �Z�b�g�������C�g��L���ɂ��邩�����ɂ��邩�ݒ肷��
void Light::LightEnable(const std::string& handlename, bool value)
{
	NoneGrow(handlename);
	SetLightEnableHandle(m_lights[handlename], value);
}

// �Z�b�g����Ă��郉�C�g�̐����擾����
int Light::IsLightNumber()
{
	return GetEnableLightHandleNum();
}

bool Light::IsEnable(const std::string& name) const
{
	auto it = m_lights.find(name);
	return it != m_lights.end() && GetLightEnableHandle(it->second) == TRUE;
}

// ���Ɏw��̃��C�g�����݂��Ă�����A�X���[����
void Light::AlreadyGrow(const std::string& handlename)
{
	if (m_lights.find(handlename) != m_lights.end())
	{
		throw std::string(handlename + "���C�g�������ЂƂ������悤�Ƃ��܂���");
	}
}

// �w��̃��C�g�����݂��Ă��Ȃ���΁A�X���[����
void Light::NoneGrow(const std::string& handlename)
{
	if (m_lights.find(handlename) == m_lights.end())
	{
		throw std::string(handlename + "���C�g�͑��݂��Ă��܂���");
	}
}