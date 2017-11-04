#pragma once

#include "EffekseerForDXLib.h"
#include"../Game/ID.h"
#include"../Math/Math.h"
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

		IsStopFlg_ = false;
	}

	//リソース
	void LoadEffect(EFFECT_ID id,const std::string& fileName) {
		effectList_[id] = LoadEffekseerEffect(fileName.c_str());
	}
	//再生
	int PlayEffect2D(EFFECT_ID id, Vector3 position = Vector3::Zero, Vector3 rotation = Vector3::Zero, Vector3 scale = Vector3::One) {
		int handle = PlayEffekseer2DEffect(effectList_[id]);
		SetScalePlayEffect2D(handle, scale);
		SetRotateEffect2D(handle, scale);
		SetPosPlayEffect2D(handle, scale);
		return handle;
	}
	int PlayEffect3D(EFFECT_ID id, Vector3 position = Vector3::Zero, Vector3 rotation = Vector3::Zero, Vector3 scale = Vector3::One) {
		int handle = PlayEffekseer3DEffect(effectList_[id]);
		SetScalePlayEffect3D(handle, scale);
		SetRotateEffect3D(handle, rotation);
		SetPosPlayEffect3D(handle, position);
		return handle;
	}
	
	//場所
	int SetPosPlayEffect3D(int handle, Vector3 position) {
		return SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);
	}
	int SetPosPlayEffect2D(int handle, Vector3 position) {
		return SetPosPlayingEffekseer2DEffect(handle, position.x, position.y , position.z);
	}
	//回転
	int SetRotateEffect3D(int handle, Vector3 rotation) {
		return SetRotationPlayingEffekseer3DEffect(handle, rotation.x, rotation.y, rotation.z);
	}
	int SetRotateEffect2D(int handle, Vector3 rotation) {
		return SetRotationPlayingEffekseer3DEffect(handle, rotation.x, rotation.y, rotation.z);
	}
	//拡大
	int SetScalePlayEffect3D(int handle, Vector3 scale) {
		return SetScalePlayingEffekseer3DEffect(handle, scale.x, scale.y, scale.z);
	}
	int SetScalePlayEffect2D(int handle, Vector3 scale) {
		return SetScalePlayingEffekseer2DEffect(handle, scale.x, scale.y, scale.z);
	}


	void Update() {
		if (IsStopFlg_) return;
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
	bool IsStopFlg_;
};