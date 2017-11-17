#pragma once


// スプライトID
enum SPRITE_ID
{
	START_SPRITE,
	END_SPRITE,
	TOTITLE_SPRITE,
	WHITE_SCREEN_SPRITE,
	BLACK_SCREEN_SPRITE,

	TITLE_START,
	TITLE_END,
	TITLE_SELECT,

	TITLE_SCREEN,

	GAUGE_UI,
	BUTTON_A,
	BUTTON_B,
	BUTTON_C,
	BUTTON_D,
	ENEMY,
	PLAYER,
	MINIMAP,
	WARNING,
	RESULT,
	JUDGE,
	JUDGE_VISION,
	SPOTLIGHT,
	POINTUP_LIGHT,
	POINTUP_AUDIENCE_RIGHT,
	POINTUP_AUDIENCE_LEFT,

	COUNT_SPRITE//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

enum EFFECT_ID {

	SAMPLE_EFFECT,
	EFFECT_TEST,
	RING_EFFECT,
	HIT_EFFECT,
	ACTION_EFFECT,
	SPIN_EFFECT,
	STEP_SUCCESS_EFFECT,
	POINT_UP_EFFECT,
	POINT_UP_BEGIN_EFFECT,
	POINT_UP_LOOP_EFFECT,
	POINT_UP_END_EFFECT,
	COL_EFFECT,
	CHARGE_START_EFFECT,
	CHARGE_EFFECT,

};

// モデルID
enum MODEL_ID
{
	//3Dモデル類
	DUMMY_MODEL,
	PLAYER_MODEL,
	ENEMY_MODEL,
	SUB_MODEL,

	SKYBOX_MODEL,
	STAGE_MODEL,

	//エフェクト類
	EFFECT_CIRCLE_MODEL,
	EFFECT_LIGHT_MODEL,
	JUST_CIRCLE_MODEL,

	COUNT_MODEL//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

// SE_ID
enum SE_ID
{
	CHECK_SE,

	COUNT_CHECK//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

// BGM_ID
enum BGM_ID
{
	TITLE_BGM,
	
	COUNT_BGM//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

enum FONT_ID {
	JAPANESE_FONT,
	DEFAULT_FONT,
	COUNT_FONT//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

enum SHADOW_MAP_ID {
	SHADOW_MAP_01,

	COUNT_SHADOW_MAP//全リソース数確認用キー(このキーにリソースを設定しないこと)
};


enum class EventMessage {

};


/*記述ルール
・Call_を必ず頭につける事
*/
enum class Notification {
	Call_CreateJustEffect,//ジャストエフェクトの生成通知
	Call_JustStep,//ジャストエフェクトの生成通知
};