#pragma once
#include"DualShockKey.h"
#include"../Math/Vector2.h"

class DualShock4Input {
private:
	DualShock4Input() {

	}
public:
	static DualShock4Input& GetInstance() {
		static DualShock4Input ds;
		return ds;
	}
	//キー入力が行われているかを調べる(DualshockKeyにキー一覧があるため、そこから持ってくる)
	bool IsStateDown(const std::pair<int, int>& keyCode)const;
	//キー入力が行われていないかを調べる(DualshockKeyにキー一覧があるため、そこから持ってくる)
	bool IsStateUp(const std::pair<int, int>& keyCode)const;
	//キー入力が行われた瞬間かを調べる(DualshockKeyにキー一覧があるため、そこから持ってくる)
	bool IsTriggerDown(const std::pair<int, int>& keyCode)const;
	//キー入力が終わった瞬間かを調べる(DualshockKeyにキー一覧があるため、そこから持ってくる)
	bool IsTriggerUp(const std::pair<int, int>& keyCode)const;
	//どこかしらのキーが押されているか
	bool GetAnyStateDown()const;

	//スティック入力を取得する、完全に0になる事が無いため、各自で小さい値を無視する事
	Vector2 GetStick()const;
	//前のスティック入力を取得する、完全に0になる事が無いため、各自で小さい値を無視する事
	Vector2 GetPrevStick()const;
	//右スティック入力を取得する、完全に0になる事が無いため、各自で小さい値を無視する事
	Vector2 GetRightStick()const;
	//前の右スティック入力を取得する、完全に0になる事が無いため、各自で小さい値を無視する事
	Vector2 GetPrevRightStick()const;
	//ハットスイッチの入力角度を取得する
	int GetPovAngle()const;
	//ハットスイッチが押されたか瞬間かどうか
	int GetPovTriggerDownAngle()const;
};
