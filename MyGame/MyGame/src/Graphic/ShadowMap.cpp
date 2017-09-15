#include "ShadowMap.h"
#include "../conv/DXConverter.h"

ShadowMap::~ShadowMap()
{
	
}

// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
void ShadowMap::Set(const std::string& handlename, Point& size)
{
	AlreadyGrow(handlename);
	m_shadowmaps[handlename] = MakeShadowMap(size.x, size.y);
}

// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
void ShadowMap::Set(const std::string& handlename, Point& size, Vector3& lightdirection)
{
	AlreadyGrow(handlename);
	m_shadowmaps[handlename] = MakeShadowMap(size.x, size.y);
	SetShadowMapLightDirection(m_shadowmaps[handlename], VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// �V���h�E�}�b�v���폜����
void ShadowMap::Delete(const std::string& handlename)
{
	NoneGrow(handlename);
	DeleteShadowMap(m_shadowmaps[handlename]);
	m_shadowmaps.erase(handlename);
}

// �z�肷�郉�C�g�̕������Z�b�g����
void ShadowMap::SetLightDirection(const std::string& handlename, const Vector3& lightdirection) const
{
	NoneGrow(handlename);
	SetShadowMapLightDirection(m_shadowmaps.at(handlename), VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
void ShadowMap::SetRange(Vector3& minpos, Vector3& maxpos) const
{
	for (const auto& shadow : m_shadowmaps)
		SetShadowMapDrawArea(shadow.second, VGet(minpos.x, minpos.y, minpos.z), VGet(maxpos.x, maxpos.y, maxpos.z));
}

void ShadowMap::Enable(int slot) const
{
	for (auto& shadow : m_shadowmaps)
		SetUseShadowMap(slot, shadow.second);
}

void ShadowMap::Disable(int slot) const
{
	for (auto& shadow : m_shadowmaps)
		SetUseShadowMap(slot, -1);
}

// �V���h�E�}�b�v���J�n����
void ShadowMap::Begin() const
{
	for (auto& shadow : m_shadowmaps)
		ShadowMap_DrawSetup(shadow.second);
}

// �V���h�E�}�b�v���I������
void ShadowMap::End() const
{
	ShadowMap_DrawEnd();
}

// ���Ɏw��̃V���h�E�}�b�v�����݂��Ă�����A�X���[����
void ShadowMap::AlreadyGrow(const std::string& handlename) const
{
	if (m_shadowmaps.find(handlename) != m_shadowmaps.end())
	{
		throw std::string(handlename + "�V���h�E�}�b�v�������ЂƂ������悤�Ƃ��܂���");
	}
}

// �w��̃V���h�E�}�b�v�����݂��Ă��Ȃ���΁A�X���[����
void ShadowMap::NoneGrow(const std::string& handlename) const
{
	if (m_shadowmaps.find(handlename) == m_shadowmaps.end())
	{
		throw std::string(handlename + "�V���h�E�}�b�v�͑��݂��Ă��܂���");
	}
}