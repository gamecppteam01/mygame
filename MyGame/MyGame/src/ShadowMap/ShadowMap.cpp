#include "ShadowMap.h"

//解像度
const Point ShadowMap::RESOLUTION_512 = Point(512, 512);
const Point ShadowMap::RESOLUTION_1024 = Point(1024, 1024);
const Point ShadowMap::RESOLUTION_2048 = Point(2048, 2048);
const Point ShadowMap::RESOLUTION_4096 = Point(4096, 4096);
const Point ShadowMap::RESOLUTION_8192 = Point(8192, 8192);
const Point ShadowMap::RESOLUTION_16384 = Point(16384, 16384);


//デストラクタ
ShadowMap::~ShadowMap(){

}

//初期化
void ShadowMap::initialize() {
	m_ShadowMaps_.clear();
}

//シャドウマップの生成
void ShadowMap::makeShadowMap(const SHADOW_MAP_ID& id, const Point& size) {
	AlreadyGrow(id);
	m_ShadowMaps_[id] = MakeShadowMap(size.x, size.y);
}

//シャドウマップの生成(ライトの方向含む)
void ShadowMap::makeShadowMap(const SHADOW_MAP_ID& id, const Point& size, const Vector3& direction) {
	AlreadyGrow(id);
	m_ShadowMaps_[id] = MakeShadowMap(size.x, size.y);
	SetLightDirection(id, direction);
}

//指定したシャドウマップの削除
void ShadowMap::DeletionShadowMap(const SHADOW_MAP_ID& id) {
	DeleteShadowMap(m_ShadowMaps_[id]);
	m_ShadowMaps_.erase(id);
}

//全てのシャドウマップの削除
void ShadowMap::AllDeletionShadowMap() {
	for (auto shadowmap : m_ShadowMaps_) {
		DeleteShadowMap(shadowmap.second);
	}
	m_ShadowMaps_.clear();
}

//指定したシャドウマップのライトの方向の設定
void ShadowMap::SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& direction) const {
	SetShadowMapLightDirection(m_ShadowMaps_.at(id), direction);
}

//全てのシャドウマップのライトの方向の設定
void ShadowMap::AllSetLightDirection(const Vector3& direction) const {
	for (auto shadowmap : m_ShadowMaps_) {
		SetShadowMapLightDirection(shadowmap.second, direction);
	}
}

//指定したシャドウマップの効果範囲の設定
void ShadowMap::SetRange(const SHADOW_MAP_ID& id, Vector3& minPos, Vector3& maxPos) const {
	SetShadowMapDrawArea(m_ShadowMaps_.at(id), minPos, maxPos);
}

//全てのシャドウマップの効果範囲の設定
void ShadowMap::AllSetRange(Vector3& minPos, Vector3& maxPos) const {
	for (auto shadowmap : m_ShadowMaps_) {
		SetShadowMapDrawArea(shadowmap.second, minPos, maxPos);
	}
}

// 指定したシャドウマップに描画する際の範囲を設定する( この関数で描画範囲を設定しない場合は視錐台を拡大した範囲が描画範囲となる )
void ShadowMap::SetAdjustDepth(const SHADOW_MAP_ID& id, float depth) const {
	SetShadowMapAdjustDepth(m_ShadowMaps_.at(id), depth);
}

// 全てのシャドウマップに描画する際の範囲を設定する( この関数で描画範囲を設定しない場合は視錐台を拡大した範囲が描画範囲となる )
void ShadowMap::AllSetAdjustDepth(float depth) const{
	for (auto shadowmap : m_ShadowMaps_) {
		SetShadowMapAdjustDepth(shadowmap.second, depth);
	}
}

//指定したシャドウマップへの描画準備
void ShadowMap::SetUp_ShadowMapDraw(const SHADOW_MAP_ID& id) const {
	ShadowMap_DrawSetup(m_ShadowMaps_.at(id));
}

//全てのシャドウマップの描画準備
void ShadowMap::AllSetUp_ShadowMapDraw() const {
	for (auto shadowmap : m_ShadowMaps_) {
		ShadowMap_DrawSetup(shadowmap.second);
	}
}

//シャドウマップへの描画を終了する
void ShadowMap::DrawEnd_ShadowMap() const {
	ShadowMap_DrawEnd();
}

//使用するシャドウマップの設定(slot0～2まで、同時に描画できるシャドウマップ数は最大３つ目で)
void ShadowMap::SetUse_ShadowMap(const SHADOW_MAP_ID& id, int slot) const {
	SetUseShadowMap(slot, m_ShadowMaps_.at(id));
}

//使用しているシャドウマップの解除
void ShadowMap::ReleaseShadowMap(int slot) const {
	SetUseShadowMap(slot, -1);
}

//シャドウマップの描画テスト
void ShadowMap::Draw_Test(const SHADOW_MAP_ID& id, Vector2& minpos, Vector2& maxpos) const {
	TestDrawShadowMap(m_ShadowMaps_.at(id), minpos.x, minpos.y, maxpos.x, maxpos.y);
}

// 既に指定のシャドウマップが存在していたら、スローする
void ShadowMap::AlreadyGrow(const SHADOW_MAP_ID& id) const
{
	if (m_ShadowMaps_.find(id) != m_ShadowMaps_.end())
	{
		throw std::string(id + "シャドウマップをもうひとつ生成しようとしました");
	}
}
