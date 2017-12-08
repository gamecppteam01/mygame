#pragma once

#include <string>
#include <unordered_map>
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../Game/ID.h"

class ShadowMap {
public:
	//コンストラクタ
	ShadowMap() = default;
	//デストラクタ
	~ShadowMap();
	//初期化
	void initialize();
	//シャドウマップの生成
	void makeShadowMap(const SHADOW_MAP_ID& id, const Point& size);
	//シャドウマップの生成(ライトの方向含む)
	void makeShadowMap(const SHADOW_MAP_ID& id, const Point& size,const Vector3& direction);
	//指定したシャドウマップの削除
	void DeletionShadowMap(const SHADOW_MAP_ID& id);
	//全てのシャドウマップの削除
	void AllDeletionShadowMap();
	//指定したシャドウマップのライトの方向の設定
	void SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& direction) const;
	//全てのシャドウマップのライトの方向の設定
	void AllSetLightDirection(const Vector3& direction) const;
	//指定したシャドウマップの効果範囲の設定
	void SetRange(const SHADOW_MAP_ID& id, Vector3& minPos, Vector3& maxPos) const;
	//全てのシャドウマップの効果範囲の設定
	void AllSetRange(Vector3& minPos, Vector3& maxPos) const;
	// 指定したシャドウマップに描画する際の範囲を設定する( この関数で描画範囲を設定しない場合は視錐台を拡大した範囲が描画範囲となる )
	void SetAdjustDepth(const SHADOW_MAP_ID& id, float depth) const;
	// 全てのシャドウマップに描画する際の範囲を設定する( この関数で描画範囲を設定しない場合は視錐台を拡大した範囲が描画範囲となる )
	void AllSetAdjustDepth(float depth) const;
	//指定したシャドウマップへの描画準備
	void SetUp_ShadowMapDraw(const SHADOW_MAP_ID& id) const;
	//全てのシャドウマップの描画準備
	void AllSetUp_ShadowMapDraw() const;
	//シャドウマップへの描画を終了する
	void DrawEnd_ShadowMap() const;
	//使用するシャドウマップの設定(slot0～2まで、同時に描画できるシャドウマップ数は最大３つ目で)
	void SetUse_ShadowMap(const SHADOW_MAP_ID& id, int slot) const;
	//使用しているシャドウマップの解除
	void ReleaseShadowMap(int slot) const;
	//シャドウマップの描画テスト
	void Draw_Test(const SHADOW_MAP_ID& id, Vector2& minpos, Vector2& maxpos) const;

private:
	
	// 既に指定のシャドウマップが存在していたら、スローする
	void AlreadyGrow(const SHADOW_MAP_ID& id) const;

private:
	std::unordered_map<SHADOW_MAP_ID, int> m_ShadowMaps_;

public:
	//解像度
	static const Point RESOLUTION_512;
	static const Point RESOLUTION_1024;
	static const Point RESOLUTION_2048;
	static const Point RESOLUTION_4096;
	static const Point RESOLUTION_8192;
	static const Point RESOLUTION_16384;
};