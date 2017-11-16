#pragma once

#include "EffekseerForDXLib.h"
#include"../Game/ID.h"
#include"../Math/Math.h"
#include<map>
#include <list>

class EffekseerManager {
private:
	EffekseerManager();

	~EffekseerManager();

public:
	static EffekseerManager &GetInstance() {
		static EffekseerManager f;
		return f;
	}
	void Initialize();

	//ÉäÉ\Å[ÉX
	void LoadEffect(EFFECT_ID id, const std::string& fileName);
	//çƒê∂
	int PlayEffect2D(EFFECT_ID id, Vector3 position = Vector3::Zero, Vector3 rotation = Vector3::Zero, Vector3 scale = Vector3::One);
	int PlayEffect3D(EFFECT_ID id, Vector3 position = Vector3::Zero, Vector3 rotation = Vector3::Zero, Vector3 scale = Vector3::One);

	void SetPositionTrackTarget(EFFECT_ID effectid, int handle, Vector3* position);

	//èÍèä
	int SetPosPlayEffect3D(int handle, Vector3 position);
	int SetPosPlayEffect2D(int handle, Vector3 position);
	//âÒì]
	int SetRotateEffect3D(int handle, Vector3 rotation);
	int SetRotateEffect2D(int handle, Vector3 rotation);
	//ägëÂ
	int SetScalePlayEffect3D(int handle, Vector3 scale);
	int SetScalePlayEffect2D(int handle, Vector3 scale);


	void Update();
	void Draw()const;
	void End();

private:
	std::map<EFFECT_ID, int> effectList_;
	std::list<std::tuple<EFFECT_ID,int,Vector3*>> trackEffectList_;
	bool IsStopFlg_;
	int handle_;
};