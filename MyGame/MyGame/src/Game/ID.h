#pragma once


// スプライトID
enum SPRITE_ID
{
	START_SPRITE,
	END_SPRITE,
	TOTITLE_SPRITE,
	WHITE_SCREEN_SPRITE,
	BLACK_SCREEN_SPRITE,
	TUTORIAL_SPRITE,
	STAGESELECT_SPRITE,
	STAGE1_TEXT_SPRITE,
	STAGE2_TEXT_SPRITE,
	STAGE3_TEXT_SPRITE,
	BACKGAME_SPRITE,
	RETRY_SPRITE,
	PAUSE_SPRITE,
	CLEAR_SPRITE,
	FADE_SPRITE,
	FACE_SPRITE,
	FACEFRAME_SPRITE,
	TEXTFRAME_SPRITE,
	LOADING_1_SPRITE,
	LOADING_2_SPRITE,
	LOADING_3_SPRITE,
	LOADING_4_SPRITE,
	LOADING_5_SPRITE,
	LOADING_6_SPRITE,

	GAMESTART_1_SPRITE,
	GAMESTART_2_SPRITE,
	GAMESTART_3_SPRITE,
	GAMESTART_START_SPRITE,

	CURSOR,
	NEXTSTAGE_SPRITE,

	TITLE_START,
	TITLE_END,
	TITLE_SELECT,

	TITLE_SCREEN,
	TITLE_LOGO,

	GAUGE_UI,
	BUTTON_A,
	BUTTON_B,
	BUTTON_C,
	BUTTON_D,
	ENEMY,
	PLAYER,
	MINIMAP,
	WARNING,
	WARNING2,
	RESULT,
	JUDGE,
	JUDGE_VISION,
	SPOTLIGHT,
	POINTUP_LIGHT,
	POINTUP_AUDIENCE_RIGHT,
	POINTUP_AUDIENCE_LEFT,
	CIRCLE_EFFECT,
	JUST_GAUGE,
	JUST_GAUGE_FRAME,
	NUMBER,
	REDNUMBER,
	NOTE,
	FINISH,

	STEP_QUARTER,
	STEP_HALF,
	STEP_SPIN,
	STEP_TURN,
	STEP_MISS,
	APPEAR_STEP_QUARTER,
	APPEAR_STEP_HALF,
	APPEAR_STEP_SPIN,
	APPEAR_STEP_TURN,
	BACK_UI,
	SELECT_BACK,
	
	CUTIN_INTRODUCT_SPRITE,
	CUTIN_LESSON1_SPRITE,
	CUTIN_LESSON2_SPRITE,
	CUTIN_LESSON3_SPRITE,
	CUTIN_LESSON4_SPRITE,
	CUTIN_LESSON5_SPRITE,
	CUTIN_LESSON_QUARTER_SPRITE,
	CUTIN_LESSON_HALF_SPRITE,
	CUTIN_LESSON_TURN_SPRITE,
	CUTIN_LESSON_SPIN_SPRITE,
	CUTIN_QUARTER_SPRITE,
	CUTIN_HALF_SPRITE,
	CUTIN_TURN_SPRITE,
	CUTIN_SPIN_SPRITE,
	CUTIN_SUCCESS_SPRITE,


	RANK_ONE_SPRITE,
	RANK_TWO_SPRITE,
	RANK_THREE_SPRITE,

	RANK_PLAYER_SPRITE,
	RANK_NAME1_SPRITE,
	RANK_NAME2_SPRITE,
	RANK_NAME3_SPRITE,
	RANK_NAME4_SPRITE,
	RANK_NAME5_SPRITE,
	RANK_NAME6_SPRITE,
	RANK_NAME7_SPRITE,
	RANK_NAME8_SPRITE,
	RANK_NAME9_SPRITE,
	RANK_NAME10_SPRITE,
	RANK_NAME11_SPRITE,
	RANK_NAME12_SPRITE,
	RANK_NAME13_SPRITE,
	RANK_NAME14_SPRITE,

	HALF_SPRITE,
    TURN_SPRITE,
    SPIN_SPRITE,
    QUATER_SPRITE,

	COMBO_POINTUP_SPRITE,
	COMBO_BURST_SPRITE,
	STAGE_1_SPRITE,
	STAGE_2_SPRITE,
	STAGE_3_SPRITE,

	TITLE_CURSOR,
	YES_TEXT,
	NO_TEXT,
	TUTORIAL_TEXT,

	AUDIENCE1,
	AUDIENCE2,
	AUDIENCE3,
	AUDIENCE4,
	AUDIENCE_MEN1,
	AUDIENCE_MEN2,
	AUDIENCE_WOMEN,

	PLAYER_SCORE,
	ENEMY1_SCORE,
	ENEMY2_SCORE,
	ENEMY3_SCORE,

	RESULT_STAGE,

	TIME_UI,

	POINTUP_SPRITE,
	BURST_SPRITE,
	NICE_SPRITE,

	COUNT_SPRITE//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

enum EFFECT_ID {

	SAMPLE_EFFECT,
	EFFECT_TEST,
	RING_EFFECT,
	HIT_EFFECT,
	ACTION_EFFECT,
	STEP_SUCCESS_EFFECT,
	POINT_UP_EFFECT,
	POINT_UP_BEGIN_EFFECT,
	POINT_UP_LOOP_EFFECT,
	POINT_UP_END_EFFECT,
	COL_EFFECT,
	CHARGE_START_EFFECT,
	CHARGE_EFFECT,
	FIRE_EFFECT,
	TUTORIALPOINT_EFFECT,
	STEP_STANDBY_INPUT1_EFFECT,
	STEP_STANDBY_INPUT2_EFFECT,

	TURN_EFFECT,
	HALF_EFFECT,
	SPIN_EFFECT,
	QUARTER_EFFECT,

};

// モデルID
enum MODEL_ID
{
	//3Dモデル類
	DUMMY_MODEL,
	PLAYER_MODEL,
	PLAYER_BULLET_MODEL,
	ENEMY_MODEL,
	BALANCEENEMY_MODEL,
	BALANCEENEMY_BULLET_MODEL,
	RIVALENEMY_MODEL,
	RIVALENEMY_BULLET_MODEL,
	SUB_MODEL,

	SKYBOX_MODEL,
	STAGE_MODEL,
	JUDGE_MODEL,
	STAGE_RIGHTLEFT_MODEL,
	STAGE_UPDOWN_MODEL,
	STAGE_WALL_CORNER_MODEL,
	STAGE_WALL_SIDE_MODEL,
	STAGE_WALL_UP_MODEL,
	STAGE_SEAT_MODEL,

	//エフェクト類
	EFFECT_CIRCLE_MODEL,
	EFFECT_LIGHT_MODEL,
	JUST_CIRCLE_MODEL,

	AUDIENCE,
	STAGE_SEAT,
	COUNT_MODEL//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

// SE_ID
enum SE_ID
{
	CHECK_SE,
	CHEER_SE,//ボーナスエリア進入時
	HIT_SE,//接触時
	COUNT_SE,//カウントダウン
	COUNT_FINISH_SE,//カウントダウン終了
	HALF_SE,//ハーフ成功時
	SPIN_SE,//スピン成功時
	TURN_SE,//ターン成功時
	QUATER_SE,//クオーター成功時
	STEP_SUCCESS_SE,//ステップ成立時
	SELECT_SE,//選択
	CURSOL_SE,//決定
	COUNT_CHECK//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

// BGM_ID
enum BGM_ID
{
	TITLE_BGM,
	STAGE1_BGM,
	STAGE2_BGM,
	STAGE3_BGM,
	CLEAR_BGM,

	COUNT_BGM//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

enum FONT_ID {
	JAPANESE_FONT,
	DEFAULT_FONT,
	BIG_FONT,
	TUTORIAL_FONT,
	COUNT_FONT//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

enum SHADOW_MAP_ID {
	SHADOW_MAP_DAMY,
	SHADOW_MAP_01,
	SHADOW_MAP_02,

	COUNT_SHADOW_MAP//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

enum class MOVIE_ID {

};


enum class EventMessage {
	Lighting,
	Extinction,
};

/*記述ルール
・Call_を必ず頭につける事
*/
enum class Notification {
	Call_CreateJustEffect,//ジャストエフェクトの生成通知
	Call_JustStep,//ジャストエフェクトの生成通知

	Call_StepSuccess,//ステップ成功時
	Call_StepFailed,//ステップ失敗時

	Call_ReciveStep,//ステップ受け取り成功
	Call_ComboStep,//コンボ

	Call_ComboParts,

	Call_Success_Combo_PointUp,//ポイントアップコンボ成功通知
	Call_Success_Combo_Burst,//バーストコンボ成功通知
	Call_Combo_End,//コンボ終了通知

	Call_Combo_Reset,
	Call_Combo_Add,
	Call_Combo_Delete,
};
