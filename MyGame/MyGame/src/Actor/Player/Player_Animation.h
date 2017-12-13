#pragma once
//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
enum class Player_Animation {
	Move_Forward = 0,//前移動時
	Idle = 1,//待機時
	Step_Left = 8,//左ステップ時
	Quarter = 2,
	Attack = 11,//攻撃時
	Shoot = 1,//発射時
	ShootEnd = 13,//発射終了
	KnockBack = 14,//被弾時
	Down = 5,//ダウン時
	Reversal = 6,//起き上がり
	Turn = 3,//回転時
	Half = 4,
	Stumble = 7,
};
