#pragma once
#include"../Math/Vector3.h"
#include"../Math/Color.h"
#include<map>
#include<string>

class LightHandle {
public:
	//コンストラクタ
	LightHandle();
	//初期化
	void initialize();
	//ライティング計算処理を使用するかどうかを設定する
	void setUseLighting(bool value);
	//ピクセルシェーダでライティング計算をするかどうか設定する
	void setUsePixelLighting(bool valeu);
	//グローバルアンビエントカラーを設定する
	void setGlobalAmbientLight(Color& color);
	//デレクショナルタイプのライトハンドルの作成
	void createDirLightHandle(const std::string& handle,const Vector3& direction);
	//ポイントタイプのライトハンドルの作成
	void createPointLightHandle(const std::string& handle, const Vector3& position, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//スポットタイプのライトハンドルの作成
	void createSpotLightHandle(const std::string& handle, const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//ライトハンドルを削除する
	void deleteLightHandle(const std::string& handle);
	//ライトハンドルを全て削除する
	void deleteLightHandleAll();
	//ライトハンドルのタイプを変更する
	void changeLightTypeHandle(const std::string& handle, int lightType);
	//ライトハンドルの有効、無効を設定する
	void setLightEnableHandle(const std::string& handle, bool value);
	//ライトハンドルのディフューズカラーを設定する
	void setLightDiffuseColorHandle(const std::string& handle, Color& color);
	//ライトハンドルのスペキュラーカラーを設定する
	void setLightSpecuarColorHandle(const std::string& handle, Color& color);
	//ライトハンドルのアンビエントカラーを設定する
	void setLightAmbientColorHandle(const std::string& handle, Color& color);
	//ライトハンドルの方向を指定する
	void setLightDirectionHandle(const std::string& handle, const Vector3& direction);
	//ライトハンドルの位置を設定する
	void setLightPositionHandle(const std::string& handle, const Vector3& position);
	//ライトハンドルの有効距離と距離減衰パラメータを設定する
	void setLightRangeAttenHandle(const std::string& handle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//ライトハンドルの照射角度パラメータを設定する
	void setLightAngleHandle(const std::string& handle, float cone_outangle, float cone_inangle);
	//ライトハンドルのタイプを取得する
	int getLightTypeHandle(const std::string& handle);
	//ライトハンドルの有効、無効を取得する
	bool getLightEnableHandle(const std::string& handle);
	//ライトハンドルのディフューズカラーを取得する
	Color getLightDiffuseColorHandle(const std::string& handle);
	//ライトハンドルのスペキュラーカラーを取得する
	Color getLightSpecuarColorHandle(const std::string& handle);
	//ライトハンドルのアンビエントカラーを取得する
	Color getLightAmbientColorHandle(const std::string& handle);
	//ライトハンドルの方向を取得する
	Vector3 getLightDirectionHandle(const std::string& handle);
	//ライトハンドルの位置を取得する
	Vector3 getLightPositionHandle(const std::string& handle);
	//有効になっているライトハンドルの数を取得する
	int getEnableLightHandleNum();
	//有効になっているライトハンドルを取得する
	int getEnableLightHandle(int index);
	//グローバルのアンビエント色を取得
	Color getGlobalAmbientColor();
public:
	static const int DirType;
	static const int PointType;
	static const int SpotType;

private:
	Color color_;
	std::map<std::string, int> lightHandles_;
};
