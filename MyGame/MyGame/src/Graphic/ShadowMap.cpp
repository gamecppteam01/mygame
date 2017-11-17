#include "ShadowMap.h"
#include "../conv/DXConverter.h"

//�𑜓x
const Point RESOLUTION_1024 = Point(1024, 1024);
const Point RESOLUTION_2048 = Point(2048, 2048);
const Point RESOLUTION_4096 = Point(4096, 4096);
const Point RESOLUTION_8192 = Point(8192, 8192);
const Point RESOLUTION_16384 = Point(16384, 16384);

ShadowMap::~ShadowMap()
{

}

// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
void ShadowMap::Set(const SHADOW_MAP_ID& id, const Point& size)
{
	AlreadyGrow(id);
	m_shadowmaps[id] = MakeShadowMap(size.x, size.y);
}

// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
void ShadowMap::Set(const SHADOW_MAP_ID& id, const Point& size, Vector3& lightdirection)
{
	AlreadyGrow(id);
	m_shadowmaps[id] = MakeShadowMap(size.x, size.y);
	SetShadowMapLightDirection(m_shadowmaps[id], VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// �V���h�E�}�b�v���폜����
void ShadowMap::Delete(const SHADOW_MAP_ID& id)
{
	NoneGrow(id);
	DeleteShadowMap(m_shadowmaps[id]);
	m_shadowmaps.erase(id);
}

// �z�肷�郉�C�g�̕������Z�b�g����
void ShadowMap::SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& lightdirection) const
{
	NoneGrow(id);
	SetShadowMapLightDirection(m_shadowmaps.at(id), VGet(lightdirection.x, lightdirection.y, lightdirection.z));
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

// �w�肵���V���h�E�}�b�v���J�n����
void ShadowMap::Begin(const SHADOW_MAP_ID& id) const
{
	ShadowMap_DrawSetup(m_shadowmaps.at(id));
}

// ���Ɏw��̃V���h�E�}�b�v�����݂��Ă�����A�X���[����
void ShadowMap::AlreadyGrow(const SHADOW_MAP_ID& id) const
{
	if (m_shadowmaps.find(id) != m_shadowmaps.end())
	{
		throw std::string(id + "�V���h�E�}�b�v�������ЂƂ������悤�Ƃ��܂���");
	}
}

// �w��̃V���h�E�}�b�v�����݂��Ă��Ȃ���΁A�X���[����
void ShadowMap::NoneGrow(const SHADOW_MAP_ID& id) const
{
	if (m_shadowmaps.find(id) == m_shadowmaps.end())
	{
		throw std::string(id + "�V���h�E�}�b�v�͑��݂��Ă��܂���");
	}
}