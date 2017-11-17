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
	/// シャドウマップをセットする（sizeは2のn乗で設定する）
	///</summary>
	void Set(const SHADOW_MAP_ID& id, const Point& size);

	///<summary>
	/// シャドウマップをセットする（ライトの設定含む,sizeは2のn乗で設定する）
	///</summary>
	void Set(const SHADOW_MAP_ID& id, const Point& size, Vector3& lightdirection);

	///<summary>
	/// シャドウマップを削除する
	///</summary>
	void Delete(const SHADOW_MAP_ID& id);

	void Clear();

	///<summary>
	/// 想定するライトの方向をセットする
	///</summary>
	void SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& lightdirection) const;

	///<summary>
	/// シャドウマップに描画する範囲を設定する
	///</summary>
	void SetRange(Vector3& minpos, Vector3& maxpos) const;

	void Enable(int slot) const ;
	//指定したシャドウマップに描画する範囲を設定する
	void Enable(const SHADOW_MAP_ID& id, int slot) const;

	void Disable(int slot) const ;
	
	///<summary>
	/// シャドウマップを開始する
	///</summary>
	void Begin() const ;

	///<summary>
	/// 指定したシャドウマップを開始する
	///</summary>
	void Begin(const SHADOW_MAP_ID& id) const;

	///<summary>
	/// シャドウマップを終了する
	///</summary>
	void End() const ;
	
private:
	///<summary>
	/// 既に指定のシャドウマップが存在していたら、スローする
	///</summary>
	void AlreadyGrow(const SHADOW_MAP_ID& id) const;

	///<summary>
	/// 指定のシャドウマップが存在していなければ、スローする
	///</summary>
	void NoneGrow(const SHADOW_MAP_ID& id) const;

	std::unordered_map<SHADOW_MAP_ID, int> m_shadowmaps;// シャドウマップ達を格納

public:
	static const Point RESOLUTION_1024;
	static const Point RESOLUTION_2048;
	static const Point RESOLUTION_4096;
	static const Point RESOLUTION_8192;
	static const Point RESOLUTION_16384;
};