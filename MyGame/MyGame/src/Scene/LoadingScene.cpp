#include "LoadingScene.h"
#include"../Resource/LoadingList.h"
#include"../Graphic/EffekseerManager.h"
#include"../DataManager/DataManager.h"
#include"../ShadowMap/ShadowMap_Data.h"
#include"../Define.h"
#include"../Graphic/DebugDraw.h"

static const std::vector<SPRITE_ID> ids_{
	SPRITE_ID::LOADING_1_SPRITE,
	SPRITE_ID::LOADING_2_SPRITE,
	SPRITE_ID::LOADING_3_SPRITE,
	SPRITE_ID::LOADING_4_SPRITE,
	SPRITE_ID::LOADING_5_SPRITE,
	SPRITE_ID::LOADING_6_SPRITE
};

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {
	Sprite::GetInstance().Load("res/Sprite/loading1.png", SPRITE_ID::LOADING_1_SPRITE);
	Sprite::GetInstance().Load("res/Sprite/loading2.png", SPRITE_ID::LOADING_2_SPRITE);
	Sprite::GetInstance().Load("res/Sprite/loading3.png", SPRITE_ID::LOADING_3_SPRITE);
	Sprite::GetInstance().Load("res/Sprite/loading4.png", SPRITE_ID::LOADING_4_SPRITE);
	Sprite::GetInstance().Load("res/Sprite/loading5.png", SPRITE_ID::LOADING_5_SPRITE);
	Sprite::GetInstance().Load("res/Sprite/loading6.png", SPRITE_ID::LOADING_6_SPRITE);
	LoadEffect();
	SetUseASyncLoadFlag(TRUE);
	//各種リソースのロードを行う
	LoadSprite();
	LoadBGM();
	LoadSE();
	LoadEtcetera();
	
	SetUseASyncLoadFlag(FALSE);
	LoadFont();

	LoadModel();
	LoadMovie();

	LoadShadowMap();

	for (auto& i : posits_) {
		i = 0.0f;
	}
	timeCount_ = 0.0f;
	keyCount_ = 0;
}

void LoadingScene::update(float deltaTime) {
	timeCount_ += deltaTime;
	if (timeCount_ >= 0.1f) {
		timeCount_ = 0.0f;
		keyCount_ = (keyCount_ + 1) % 6;
	}

	if (GetASyncLoadNum() == 0) {
		isEnd_ = true;
	}
}

void LoadingScene::draw() const {
	float size = 0.5f;
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::LOADING_1_SPRITE) / 2;
	Sprite::GetInstance().Draw(ids_.at(keyCount_), SCREEN_SIZE*0.5f, origin, Vector2::One*size);
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", GetASyncLoadNum());
}

void LoadingScene::end() {

}

void LoadingScene::LoadSprite()
{
	std::string defaultPath = "res/Sprite/";//全リソース共通パス
	Sprite::GetInstance().Load(defaultPath + "gamestartText.png", SPRITE_ID::START_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "tutorial.png", SPRITE_ID::TUTORIAL_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "gameend.png", SPRITE_ID::END_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "totitle.png", SPRITE_ID::TOTITLE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "whitescreen.png", SPRITE_ID::WHITE_SCREEN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "blackscreen.png", SPRITE_ID::BLACK_SCREEN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "TestTitleStart.png", SPRITE_ID::TITLE_START);
	Sprite::GetInstance().Load(defaultPath + "TestTitleEnd.png", SPRITE_ID::TITLE_END);
	Sprite::GetInstance().Load(defaultPath + "TestTitleSelect.png", SPRITE_ID::TITLE_SELECT);
	Sprite::GetInstance().Load(defaultPath + "result.png", SPRITE_ID::RESULT);
	Sprite::GetInstance().Load(defaultPath + "stageselect.png", SPRITE_ID::STAGESELECT_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "backgame.png", SPRITE_ID::BACKGAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "stage1.png", SPRITE_ID::STAGE1_TEXT_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "stage2.png", SPRITE_ID::STAGE2_TEXT_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "stage3.png", SPRITE_ID::STAGE3_TEXT_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "retry.png", SPRITE_ID::RETRY_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "pause.png", SPRITE_ID::PAUSE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "cursor.png", SPRITE_ID::CURSOR);
	Sprite::GetInstance().Load(defaultPath + "nextstage.png", SPRITE_ID::NEXTSTAGE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "clear.png", SPRITE_ID::CLEAR_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "sceneMove.png", SPRITE_ID::FADE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "tutorialText.png", SPRITE_ID::TUTORIAL_TEXT);
	Sprite::GetInstance().Load(defaultPath + "YESText.png", SPRITE_ID::YES_TEXT);
	Sprite::GetInstance().Load(defaultPath + "NOText.png", SPRITE_ID::NO_TEXT);
	

	Sprite::GetInstance().Load(defaultPath + "Enemy.png",   SPRITE_ID::ENEMY);
	Sprite::GetInstance().Load(defaultPath + "Player.png",  SPRITE_ID::PLAYER);
	Sprite::GetInstance().Load(defaultPath + "MiniMapScreen.png", SPRITE_ID::MINIMAP);
	Sprite::GetInstance().Load(defaultPath + "Judge.png", SPRITE_ID::JUDGE);
	Sprite::GetInstance().Load(defaultPath + "Judge_Vision.png", SPRITE_ID::JUDGE_VISION);
	Sprite::GetInstance().Load(defaultPath + "arrow.png", SPRITE_ID::WARNING);
	Sprite::GetInstance().Load(defaultPath + "arrow2.png", SPRITE_ID::WARNING2);
	Sprite::GetInstance().Load(defaultPath + "titleBack.png", SPRITE_ID::TITLE_SCREEN);
	Sprite::GetInstance().Load(defaultPath + "ShallWeDance!!.png", SPRITE_ID::TITLE_LOGO);
	Sprite::GetInstance().Load(defaultPath + "pointUp_side.png", SPRITE_ID::POINTUP_LIGHT);
	Sprite::GetInstance().Load(defaultPath + "audience_left.png", SPRITE_ID::POINTUP_AUDIENCE_LEFT);
	Sprite::GetInstance().Load(defaultPath + "audience_right.png", SPRITE_ID::POINTUP_AUDIENCE_RIGHT);
	Sprite::GetInstance().Load(defaultPath + "Effect/justcircle.png", SPRITE_ID::CIRCLE_EFFECT);
	Sprite::GetInstance().Load(defaultPath + "stepgauge.png", SPRITE_ID::JUST_GAUGE);
	Sprite::GetInstance().Load(defaultPath + "stepgaugeframe.png", SPRITE_ID::JUST_GAUGE_FRAME);
	Sprite::GetInstance().Load(defaultPath + "numbers.png", SPRITE_ID::NUMBER);
	Sprite::GetInstance().Load(defaultPath + "rednumbers.png", SPRITE_ID::REDNUMBER);
	Sprite::GetInstance().Load(defaultPath + "finish.png", SPRITE_ID::FINISH);
	Sprite::GetInstance().Load(defaultPath + "note.png", SPRITE_ID::NOTE);
	Sprite::GetInstance().Load(defaultPath + "step_quarter.png", SPRITE_ID::STEP_QUARTER);
	Sprite::GetInstance().Load(defaultPath + "step_half.png", SPRITE_ID::STEP_HALF);
	Sprite::GetInstance().Load(defaultPath + "step_spin.png", SPRITE_ID::STEP_SPIN);
	Sprite::GetInstance().Load(defaultPath + "step_turn.png", SPRITE_ID::STEP_TURN);
	Sprite::GetInstance().Load(defaultPath + "step_miss.png", SPRITE_ID::STEP_MISS);
	Sprite::GetInstance().Load(defaultPath + "step_quarter2.png", SPRITE_ID::APPEAR_STEP_QUARTER);
	Sprite::GetInstance().Load(defaultPath + "step_half2.png", SPRITE_ID::APPEAR_STEP_HALF);
	Sprite::GetInstance().Load(defaultPath + "step_spin2.png", SPRITE_ID::APPEAR_STEP_SPIN);
	Sprite::GetInstance().Load(defaultPath + "step_turn2.png", SPRITE_ID::APPEAR_STEP_TURN);
	Sprite::GetInstance().Load(defaultPath + "back_UI.png", SPRITE_ID::BACK_UI);
	Sprite::GetInstance().Load(defaultPath + "selectback.png", SPRITE_ID::SELECT_BACK);
	Sprite::GetInstance().Load(defaultPath + "face.png", SPRITE_ID::FACE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "teacherFrame.png", SPRITE_ID::FACEFRAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "messageFrame.png", SPRITE_ID::TEXTFRAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "quarter_sprite.png", SPRITE_ID::QUATER_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "turn_sprite.png", SPRITE_ID::TURN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "spin_sprite.png", SPRITE_ID::SPIN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "half_sprite.png", SPRITE_ID::HALF_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "half_sprite.png", SPRITE_ID::HALF_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Introduction_Cutin.png", SPRITE_ID::CUTIN_INTRODUCT_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Lesson1_Cutin.png", SPRITE_ID::CUTIN_LESSON1_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Lesson2_Cutin.png", SPRITE_ID::CUTIN_LESSON2_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Lesson3_Cutin.png", SPRITE_ID::CUTIN_LESSON3_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Lesson4_Cutin.png", SPRITE_ID::CUTIN_LESSON4_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Lesson5_Cutin.png", SPRITE_ID::CUTIN_LESSON5_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "step1_Cutin.png", SPRITE_ID::CUTIN_LESSON_QUARTER_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "step2_Cutin.png", SPRITE_ID::CUTIN_LESSON_TURN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "step3_Cutin.png", SPRITE_ID::CUTIN_LESSON_HALF_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "step4_Cutin.png", SPRITE_ID::CUTIN_LESSON_SPIN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Half_Cutin.png", SPRITE_ID::CUTIN_HALF_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Quarter_Cutin.png", SPRITE_ID::CUTIN_QUARTER_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Spin_Cutin.png", SPRITE_ID::CUTIN_SPIN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Success_Cutin.png", SPRITE_ID::CUTIN_SUCCESS_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "Turn_Cutin.png", SPRITE_ID::CUTIN_TURN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "titlecursor.png", SPRITE_ID::TITLE_CURSOR);
	Sprite::GetInstance().Load(defaultPath + "burstcomboUI.png", SPRITE_ID::COMBO_BURST_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "pointupcomboUI.png", SPRITE_ID::COMBO_POINTUP_SPRITE);

	Sprite::GetInstance().Load(defaultPath + "lightgauge.png", SPRITE_ID::LIGHT_GAUGE_SPRITE);
	
	Sprite::GetInstance().Load(defaultPath + "nameSetFrame.png", SPRITE_ID::KEYBOARD_FRAME_SPRITE);
	
	Sprite::GetInstance().Load(defaultPath + "stage1name.png", SPRITE_ID::STAGE_1_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "stage2name.png", SPRITE_ID::STAGE_2_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "stage3name.png", SPRITE_ID::STAGE_3_SPRITE);

	Sprite::GetInstance().Load(defaultPath + "countDown1.png", SPRITE_ID::GAMESTART_1_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "countDown2.png", SPRITE_ID::GAMESTART_2_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "countDown3.png", SPRITE_ID::GAMESTART_3_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "start.png", SPRITE_ID::GAMESTART_START_SPRITE);

	Sprite::GetInstance().Load(defaultPath + "topIcon.png", SPRITE_ID::RANK_ONE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "secondIcon.png", SPRITE_ID::RANK_TWO_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "thirdIcon.png", SPRITE_ID::RANK_THREE_SPRITE);
	
	Sprite::GetInstance().Load(defaultPath + "playerNameframe.png", SPRITE_ID::RANK_PLAYER_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame001.png", SPRITE_ID::RANK_NAME1_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame002.png", SPRITE_ID::RANK_NAME2_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame003.png", SPRITE_ID::RANK_NAME3_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame004.png", SPRITE_ID::RANK_NAME4_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame005.png", SPRITE_ID::RANK_NAME5_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame006.png", SPRITE_ID::RANK_NAME6_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame007.png", SPRITE_ID::RANK_NAME7_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame008.png", SPRITE_ID::RANK_NAME8_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame009.png", SPRITE_ID::RANK_NAME9_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame010.png", SPRITE_ID::RANK_NAME10_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame011.png", SPRITE_ID::RANK_NAME11_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame012.png", SPRITE_ID::RANK_NAME12_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame013.png", SPRITE_ID::RANK_NAME13_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFrame014.png", SPRITE_ID::RANK_NAME14_SPRITE);

	Sprite::GetInstance().Load(defaultPath + "audience1.png", SPRITE_ID::AUDIENCE1);
	Sprite::GetInstance().Load(defaultPath + "audience2.png", SPRITE_ID::AUDIENCE2);
	Sprite::GetInstance().Load(defaultPath + "audience3.png", SPRITE_ID::AUDIENCE3);
	Sprite::GetInstance().Load(defaultPath + "audience4.png", SPRITE_ID::AUDIENCE4);
	Sprite::GetInstance().Load(defaultPath + "audience_men001.png", SPRITE_ID::AUDIENCE_MEN1);
	Sprite::GetInstance().Load(defaultPath + "audience_men002.png", SPRITE_ID::AUDIENCE_MEN2);
	Sprite::GetInstance().Load(defaultPath + "audience_men003.png", SPRITE_ID::AUDIENCE_MEN3);
	Sprite::GetInstance().Load(defaultPath + "audience_women001.png", SPRITE_ID::AUDIENCE_WOMEN1);
	Sprite::GetInstance().Load(defaultPath + "audience_women002.png", SPRITE_ID::AUDIENCE_WOMEN2);
	Sprite::GetInstance().Load(defaultPath + "audience_women003.png", SPRITE_ID::AUDIENCE_WOMEN3);

	//Sprite::GetInstance().Load(defaultPath + "score_player.png", SPRITE_ID::PLAYER_SCORE);
	//Sprite::GetInstance().Load(defaultPath + "score_enemy1.png", SPRITE_ID::ENEMY1_SCORE);
	//Sprite::GetInstance().Load(defaultPath + "score_enemy2.png", SPRITE_ID::ENEMY2_SCORE);
	//Sprite::GetInstance().Load(defaultPath + "score_enemy3.png", SPRITE_ID::ENEMY3_SCORE);

	Sprite::GetInstance().Load(defaultPath + "clock.png", SPRITE_ID::TIME_UI);
	//Sprite::GetInstance().Load(defaultPath + "burst_ui.png", SPRITE_ID::BURST_SPRITE);
	//Sprite::GetInstance().Load(defaultPath + "pointup_ui.png", SPRITE_ID::POINTUP_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nice_sprite.png", SPRITE_ID::NICE_SPRITE);
	//Sprite::GetInstance().Load(defaultPath + "titlecursorflash.png", SPRITE_ID::CURSOR_FLASH);
	Sprite::GetInstance().Load(defaultPath + "flash.png", SPRITE_ID::FLASH_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameFramePlayer.png", SPRITE_ID::TEST_PLAYER_RANK_SPRITE);

	Sprite::GetInstance().Load(defaultPath + "movieFrame2.png", SPRITE_ID::MOVIE_FRAME);

	//Sprite::GetInstance().Load(defaultPath + "charChoiceFrame_L.png", SPRITE_ID::KEYBOARD_CURSOR_L_SPRITE);
	//Sprite::GetInstance().Load(defaultPath + "charChoiceFrame_R.png", SPRITE_ID::KEYBOARD_CURSOR_R_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameCursor_L.png", SPRITE_ID::NAME_CURSOL_L_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameCursor_R.png", SPRITE_ID::NAME_CURSOL_R_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "inputNameFrame.png", SPRITE_ID::INPUT_NAMEFRAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameCheck_Yes.png", SPRITE_ID::NAMECHECK_YES_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameCheck_No.png", SPRITE_ID::NAMECHECK_NO_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "nameCheckFrame.png", SPRITE_ID::NAMECHECK_FRAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "player1_nameMesse.png", SPRITE_ID::PLAYER1_NAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "player2_nameMesse.png", SPRITE_ID::PLAYER2_NAME_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "tutorialTexture.png", SPRITE_ID::TUTORIAL_HAVE_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "lessonLine1.png", SPRITE_ID::TutorialSprite1);
	Sprite::GetInstance().Load(defaultPath + "lessonLine2.png", SPRITE_ID::TutorialSprite2);
	Sprite::GetInstance().Load(defaultPath + "lessonLine3.png", SPRITE_ID::TutorialSprite3);
	Sprite::GetInstance().Load(defaultPath + "lessonLine4.png", SPRITE_ID::TutorialSprite4);
	Sprite::GetInstance().Load(defaultPath + "lessonLine5.png", SPRITE_ID::TutorialSprite5);
	Sprite::GetInstance().Load(defaultPath + "lessonLine6.png", SPRITE_ID::TutorialSprite6);
	Sprite::GetInstance().Load(defaultPath + "lessonLine7.png", SPRITE_ID::TutorialSprite7);
	
}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//全リソース共通パス
	Model::GetInstance().Load(defaultPath + "player/player_men/player_men.mv1", MODEL_ID::PLAYER_MODEL);
	Model::GetInstance().Load(defaultPath + "player/player_women/player_women.mv1", MODEL_ID::PLAYER_BULLET_MODEL);
	Model::GetInstance().Load(defaultPath + "enemy/balanceEnemy_men/balanceEnemy_men.mv1", MODEL_ID::BALANCEENEMY_MODEL);
	Model::GetInstance().Load(defaultPath + "enemy/balanceEnemy_women/balanceEnemy_women.mv1", MODEL_ID::BALANCEENEMY_BULLET_MODEL);
	Model::GetInstance().Load(defaultPath + "enemy/rivalEnemy_men/rivalEnemy_men.mv1", MODEL_ID::RIVALENEMY_MODEL);
	Model::GetInstance().Load(defaultPath + "enemy/rivalEnemy_women/rivalEnemy_women.mv1", MODEL_ID::RIVALENEMY_BULLET_MODEL);
	Model::GetInstance().Load(defaultPath + "judge/judgemodel.mv1", MODEL_ID::JUDGE_MODEL);
	//Model::GetInstance().Load(defaultPath + "enemy/noticeEnemy_men/balanceEnemy_men.mv1", MODEL_ID::NOTICEENEMY_MODEL);
	//Model::GetInstance().Load(defaultPath + "enemy/noticeEnemy_women/balanceEnemy_women.mv1", MODEL_ID::NOTICEENEMY_BULLET_MODEL);
}


void LoadingScene::LoadMovie(){
	std::string defaultPath = "res/Movie/";
	Movie::GetInstance().Load(MOVIE_ID::QUARTER, defaultPath + "quarter.mp4");
	Movie::GetInstance().Load(MOVIE_ID::HALF, defaultPath + "half.mp4");
	Movie::GetInstance().Load(MOVIE_ID::SPIN, defaultPath + "spin.mp4");
	Movie::GetInstance().Load(MOVIE_ID::TURN, defaultPath + "turn.mp4");
}

void LoadingScene::LoadEffect()
{
	//Modelクラスを利用したエフェクト
	std::string defaultPath = "res/Sprite/Effect/";//全リソース共通パス
	Model::GetInstance().Load2D(defaultPath + "circleeffect.png", MODEL_ID::EFFECT_CIRCLE_MODEL);
	Model::GetInstance().Load2D(defaultPath + "light.png", MODEL_ID::EFFECT_LIGHT_MODEL);
	Model::GetInstance().Load2D(defaultPath + "justcircle.png", MODEL_ID::JUST_CIRCLE_MODEL);

	//Effekseerを利用したエフェクト
	defaultPath = "res/Effekseer/";
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::SAMPLE_EFFECT, defaultPath+"laser.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::EFFECT_TEST, defaultPath + "testeffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::STEP_SUCCESS_EFFECT, defaultPath + "stepSuccess.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_EFFECT, defaultPath + "pueffect/pointUp_blow.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_BEGIN_EFFECT, defaultPath + "pueffect/pointUp_fadeIn.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_LOOP_EFFECT, defaultPath + "pueffect/pointUp.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_END_EFFECT, defaultPath + "pueffect/pointUp_fadeOut.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::COL_EFFECT, defaultPath + "collision.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::CHARGE_START_EFFECT, defaultPath + "charge_Start.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::CHARGE_EFFECT, defaultPath + "charge.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::FIRE_EFFECT, defaultPath + "fire.efk");
	//仮エフェクト
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::RING_EFFECT, defaultPath + "ringeffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::HIT_EFFECT, defaultPath + "hiteffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::ACTION_EFFECT, defaultPath + "actioneffect.efk");
	
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::TUTORIALPOINT_EFFECT, defaultPath + "tutorialPoint.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::STEP_STANDBY_INPUT1_EFFECT, defaultPath + "stepStandby1.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::STEP_STANDBY_INPUT2_EFFECT, defaultPath + "stepStandby2.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::TURN_EFFECT, defaultPath + "turnEffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::QUARTER_EFFECT, defaultPath + "quaterEffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::HALF_EFFECT, defaultPath + "halfEffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::SPIN_EFFECT, defaultPath + "Spin.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::SPIN_SHIELD_EFFECT, defaultPath + "shield_spin.efk");

	
}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//全リソース共通パス
	FontManager::GetInstance().AddFont(FONT_ID::JAPANESE_FONT, defaultPath + "HGRGY.TTC", "HG行書体", 50);
	FontManager::GetInstance().AddFont(FONT_ID::DEFAULT_FONT, defaultPath + "KILLGOTHIC.TTC", "Killゴシック", 50);
	FontManager::GetInstance().AddFont(FONT_ID::INPUT_SIZE_FONT, defaultPath + "KILLGOTHIC.TTC", "Killゴシック", 101);
	FontManager::GetInstance().AddFont(FONT_ID::BIG_FONT , defaultPath + "KILLGOTHIC.TTC", "Killゴシック", 140);
	FontManager::GetInstance().AddFont(FONT_ID::TUTORIAL_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 70);
	FontManager::GetInstance().AddFont(FONT_ID::KEYBOARD_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 60);
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_UNDER_5_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 166);
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_6_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 150);
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_7_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 138);
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_8_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 125);
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_9_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 116);
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_10_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 108);

	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_SMALL_UNDER_5_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(166*0.4f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_SMALL_6_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(150*0.4f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_SMALL_7_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(138*0.4f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_SMALL_8_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(125*0.4f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_SMALL_9_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(116*0.4f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_SMALL_10_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ",(int)(108*0.4f));

	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_RANK_UNDER_5_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(166 * 0.2f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_RANK_6_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(150 * 0.2f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_RANK_7_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(138 * 0.2f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_RANK_8_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(125 * 0.2f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_RANK_9_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(116 * 0.2f));
	FontManager::GetInstance().AddFont(FONT_ID::CUTIN_RANK_10_FONT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", (int)(108 * 0.2f));

}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//全リソース共通パス
	Sound::GetInstance().LoadBGM(defaultPath + "title.mp3", BGM_ID::TITLE_BGM);
	Sound::GetInstance().LoadBGM(defaultPath + "stage1c_bgm.mp3", BGM_ID::STAGE1_BGM);
	Sound::GetInstance().LoadBGM(defaultPath + "stage2b_bgm.wav", BGM_ID::STAGE2_BGM);
	Sound::GetInstance().LoadBGM(defaultPath + "stage3b_bgm.wav", BGM_ID::STAGE3_BGM);
	Sound::GetInstance().LoadBGM(defaultPath + "clear.mp3", BGM_ID::CLEAR_BGM);
}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//全リソース共通パス
	Sound::GetInstance().LoadSE(defaultPath + "check.mp3", SE_ID::CHECK_SE);
	Sound::GetInstance().LoadSE(defaultPath + "cheer2_se.mp3", SE_ID::CHEER_SE);
	Sound::GetInstance().LoadSE(defaultPath + "hit_se.mp3", SE_ID::HIT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "count_se.mp3", SE_ID::COUNT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "countFinish_se.mp3", SE_ID::COUNT_FINISH_SE);
	Sound::GetInstance().LoadSE(defaultPath + "stepSuccess_se.mp3", SE_ID::STEP_SUCCESS_SE);
	Sound::GetInstance().LoadSE(defaultPath + "cursol.mp3", SE_ID::CURSOL_SE);
	Sound::GetInstance().LoadSE(defaultPath + "systemse.mp3", SE_ID::SELECT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "half_se.mp3", SE_ID::HALF_SE);
	Sound::GetInstance().LoadSE(defaultPath + "spin_se.wav", SE_ID::SPIN_SE);
	Sound::GetInstance().LoadSE(defaultPath + "quarter_se.mp3", SE_ID::QUATER_SE);
	Sound::GetInstance().LoadSE(defaultPath + "turn_se.mp3", SE_ID::TURN_SE);
	Sound::GetInstance().SetSEVolume(SE_ID::HIT_SE, 1.0f);
}

//シャドウマップの読み込み
void LoadingScene::LoadShadowMap()
{
	DataManager::GetInstance().setShadowData(MODEL_ID::STAGE_MODEL,
											ShadowMap_Data(SHADOW_MAP_ID::SHADOW_MAP_01, 
											Point(512, 512), 
											-Vector3::Up, 
											Vector3(-150.0f, -2.5f, -75.0f),
											Vector3(150.0f, 15.0f, 75.0f), 0));
	DataManager::GetInstance().setShadowData(MODEL_ID::STAGE_MODEL,
											ShadowMap_Data(SHADOW_MAP_ID::SHADOW_MAP_02,
											Point(512, 512),
											-Vector3::Up,
											Vector3(-120.0f, -2.5f, -60.0f),
											Vector3(120.0f, 15.0f, 60.0f), 0));
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//全リソース共通パス
	Model::GetInstance().Load(defaultPath + "Skybox/skydome.mv1", MODEL_ID::SKYBOX_MODEL);
	Model::GetInstance().Load(defaultPath + "Stage/field/field.mv1", MODEL_ID::STAGE_MODEL);
	Model::GetInstance().Load(defaultPath + "Stage/field/field_Side.mv1", MODEL_ID::STAGE_RIGHTLEFT_MODEL);
	Model::GetInstance().Load(defaultPath + "Stage/field/field_Updown.mv1", MODEL_ID::STAGE_UPDOWN_MODEL);
	//Model::GetInstance().Load(defaultPath + "Stage/field/wall_corner.mv1", MODEL_ID::STAGE_WALL_CORNER_MODEL);
	//Model::GetInstance().Load(defaultPath + "Stage/field/wall_side.mv1", MODEL_ID::STAGE_WALL_SIDE_MODEL);
	//Model::GetInstance().Load(defaultPath + "Stage/field/wall_up.mv1", MODEL_ID::STAGE_WALL_UP_MODEL);
	//Model::GetInstance().Load(defaultPath + "Stage/field/audience.mv1", MODEL_ID::AUDIENCE);
	Model::GetInstance().Load(defaultPath + "Stage/audienceSeat/audienceSeat.mv1", MODEL_ID::STAGE_SEAT);

}
