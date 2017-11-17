#include "ShadowMap.h"
#include "../conv/DXConverter.h"

//解像度
const Point RESOLUTION_1024 = Point(1024, 1024);
const Point RESOLUTION_2048 = Point(2048, 2048);
const Point RESOLUTION_4096 = Point(4096, 4096);
const Point RESOLUTION_8192 = Point(8192, 8192);
const Point RESOLUTION_16384 = Point(16384, 16384);

ShadowMap::~ShadowMap()
{

}

// シャドウマップをセットする（sizeは2のn乗で設定する）
void ShadowMap::Set(const SHADOW_MAP_ID& id, const Point& size)
{
	AlreadyGrow(id);
	m_shadowmaps[id] = MakeShadowMap(size.x, size.y);
}

// シャドウマップをセットする（sizeは2のn乗で設定する）
void ShadowMap::Set(const SHADOW_MAP_ID& id, const Point& size, Vector3& lightdirection)
{
	AlreadyGrow(id);
	m_shadowmaps[id] = MakeShadowMap(size.x, size.y);
	SetShadowMapLightDirection(m_shadowmaps[id], VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// シャドウマップを削除する
void ShadowMap::Delete(const SHADOW_MAP_ID& id)
{
	NoneGrow(id);
	DeleteShadowMap(m_shadowmaps[id]);
	m_shadowmaps.erase(id);
}

// 想定するライトの方向をセットする
void ShadowMap::SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& lightdirection) const
{
	NoneGrow(id);
	SetShadowMapLightDirection(m_shadowmaps.at(id), VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// シャドウマップに描画する範囲を設定する
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

// シャドウマップを開始する
void ShadowMap::Begin() const
{
	for (auto& shadow : m_shadowmaps)
		ShadowMap_DrawSetup(shadow.second);
}

// シャドウマップを終了する
void ShadowMap::End() const
{
	ShadowMap_DrawEnd();
}

// 指定したシャドウマップを開始する
void ShadowMap::Begin(const SHADOW_MAP_ID& id) const
{
	ShadowMap_DrawSetup(m_shadowmaps.at(id));
}

// 既に指定のシャドウマップが存在していたら、スローする
void ShadowMap::AlreadyGrow(const SHADOW_MAP_ID& id) const
{
	if (m_shadowmaps.find(id) != m_shadowmaps.end())
	{
		throw std::string(id + "シャドウマップをもうひとつ生成しようとしました");
	}
}

// 指定のシャドウマップが存在していなければ、スローする
void ShadowMap::NoneGrow(const SHADOW_MAP_ID& id) const
{
	if (m_shadowmaps.find(id) == m_shadowmaps.end())
	{
		throw std::string(id + "シャドウマップは存在していません");
	}
}