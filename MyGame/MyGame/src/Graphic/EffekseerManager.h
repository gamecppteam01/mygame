#pragma once

#include "EffekseerForDXLib.h"
#include"../Game/ID.h"
#include<map>

class EffekseerManager {
private:
	EffekseerManager() {
		Initialize();
	}

public:
	static EffekseerManager &GetInstance() {
		static EffekseerManager f;
		return f;
	}
	void Initialize() {
		if (Effkseer_Init(2000) == -1)return;

		// Zバッファを有効にする。
		// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
		SetUseZBuffer3D(TRUE);

		// Zバッファへの書き込みを有効にする。
		// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
		SetWriteZBuffer3D(TRUE);

		// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
		// Effekseerを使用する場合は必ず設定する。
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
		// DXライブラリのデバイスロストした時のコールバックを設定する。
		// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
		// ただし、DirectX11を使用する場合は実行する必要はない。
		Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	}
	//リソース
	void LoadEffect(EFFECT_ID id,const std::string& fileName) {
		effectList_[id] = LoadEffekseerEffect(fileName.c_str());
	}
	void PlayEffect2D(EFFECT_ID id) {
		PlayEffekseer2DEffect(effectList_[id]);
	}
	void PlayEffect3D(EFFECT_ID id) {
		PlayEffekseer3DEffect(effectList_[id]);
	}

	void Update() {
		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();
		
		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer3D();

	}
	void Draw()const {
		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer3D();
	}
	void End() {
		effectList_.clear();
		Effkseer_End();
	}

private:
	std::map<EFFECT_ID, int> effectList_;
};