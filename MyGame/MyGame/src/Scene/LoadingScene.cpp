#include "LoadingScene.h"
#include"../Resource/LoadingList.h"
#include"../Graphic/EffekseerManager.h"

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {
	//各種リソースのロードを行う
	LoadSprite();
	LoadModel();
	LoadEffect();
	LoadFont();
	LoadBGM();
	LoadSE();
	LoadEtcetera();

	isEnd_ = true;
}

void LoadingScene::update(float deltaTime) {

}

void LoadingScene::draw() const {

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

	Sprite::GetInstance().Load(defaultPath + "gauge.png",   SPRITE_ID::GAUGE_UI);
	Sprite::GetInstance().Load(defaultPath + "ButtonA.png", SPRITE_ID::BUTTON_A);
	Sprite::GetInstance().Load(defaultPath + "ButtonB.png", SPRITE_ID::BUTTON_B);
	Sprite::GetInstance().Load(defaultPath + "ButtonC.png", SPRITE_ID::BUTTON_C);
	Sprite::GetInstance().Load(defaultPath + "ButtonD.png", SPRITE_ID::BUTTON_D);
	Sprite::GetInstance().Load(defaultPath + "Enemy.png",   SPRITE_ID::ENEMY);
	Sprite::GetInstance().Load(defaultPath + "Player.png",  SPRITE_ID::PLAYER);
	Sprite::GetInstance().Load(defaultPath + "MiniMapScreen.png", SPRITE_ID::MINIMAP);
	Sprite::GetInstance().Load(defaultPath + "Judge.png", SPRITE_ID::JUDGE);
	Sprite::GetInstance().Load(defaultPath + "Judge_Vision.png", SPRITE_ID::JUDGE_VISION);
	Sprite::GetInstance().Load(defaultPath + "SpotLight.png", SPRITE_ID::SPOTLIGHT);
	Sprite::GetInstance().Load(defaultPath + "arrow.png", SPRITE_ID::WARNING);
	Sprite::GetInstance().Load(defaultPath + "arrow2.png", SPRITE_ID::WARNING2);
	Sprite::GetInstance().Load(defaultPath + "titlescreen.png", SPRITE_ID::TITLE_SCREEN);
	Sprite::GetInstance().Load(defaultPath + "pointUp_side.png", SPRITE_ID::POINTUP_LIGHT);
	Sprite::GetInstance().Load(defaultPath + "audience_left.png", SPRITE_ID::POINTUP_AUDIENCE_LEFT);
	Sprite::GetInstance().Load(defaultPath + "audience_right.png", SPRITE_ID::POINTUP_AUDIENCE_RIGHT);
	Sprite::GetInstance().Load(defaultPath + "Effect/justcircle.png", SPRITE_ID::CIRCLE_EFFECT);
	Sprite::GetInstance().Load(defaultPath + "stepgauge.png", SPRITE_ID::JUST_GAUGE);
	Sprite::GetInstance().Load(defaultPath + "stepgaugeframe.png", SPRITE_ID::JUST_GAUGE_FRAME);
	Sprite::GetInstance().Load(defaultPath + "numbers.png", SPRITE_ID::NUMBER);
	Sprite::GetInstance().Load(defaultPath + "rednumbers.png", SPRITE_ID::REDNUMBER);
	
		
}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//全リソース共通パス
	Model::GetInstance().Load(defaultPath + "player/player_men/player_men.pmx", MODEL_ID::PLAYER_MODEL);
	Model::GetInstance().Load(defaultPath + "player/player_women/player_women.pmx", MODEL_ID::PLAYER_BULLET_MODEL);
	Model::GetInstance().Load(defaultPath + "ghoul.mv1", MODEL_ID::ENEMY_MODEL);
	Model::GetInstance().Load(defaultPath + "enemy/balanceEnemy_men/balanceEnemy_men.pmx", MODEL_ID::BALANCEENEMY_MODEL);
	Model::GetInstance().Load(defaultPath + "enemy/balanceEnemy_women/balanceEnemy_women.pmd", MODEL_ID::BALANCEENEMY_BULLET_MODEL);
	
	Model::GetInstance().Load(defaultPath + "lightPanel.mv1", MODEL_ID::EFFECT_LIGHT_MODEL);
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
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::SPIN_EFFECT, defaultPath + "Spin.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::STEP_SUCCESS_EFFECT, defaultPath + "stepSuccess.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_EFFECT, defaultPath + "pueffect/pointUp_blow.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_BEGIN_EFFECT, defaultPath + "pueffect/pointUp_fadeIn.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_LOOP_EFFECT, defaultPath + "pueffect/pointUp.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::POINT_UP_END_EFFECT, defaultPath + "pueffect/pointUp_fadeOut.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::COL_EFFECT, defaultPath + "collision.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::CHARGE_START_EFFECT, defaultPath + "charge_Start.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::CHARGE_EFFECT, defaultPath + "charge.efk");
	//仮エフェクト
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::RING_EFFECT, defaultPath + "ringeffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::HIT_EFFECT, defaultPath + "hiteffect.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::ACTION_EFFECT, defaultPath + "actioneffect.efk");
}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//全リソース共通パス
	FontManager::GetInstance().AddFont(FONT_ID::JAPANESE_FONT, defaultPath + "HGRGY.TTC", "HG行書体", 50);
	FontManager::GetInstance().AddFont(FONT_ID::DEFAULT_FONT, defaultPath + "KILLGOTHIC.TTC", "Killゴシック", 50);
}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//全リソース共通パス
	Sound::GetInstance().LoadBGM(defaultPath + "title.mp3", BGM_ID::TITLE_BGM);

}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//全リソース共通パス
	Sound::GetInstance().LoadSE(defaultPath + "check.mp3", SE_ID::CHECK_SE);
	Sound::GetInstance().LoadSE(defaultPath + "cheer2_se.mp3", SE_ID::CHEER_SE);
	Sound::GetInstance().LoadSE(defaultPath + "hit_se.mp3", SE_ID::HIT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "count_se.mp3", SE_ID::COUNT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "countFinish_se.mp3", SE_ID::COUNT_FINISH_SE);
	Sound::GetInstance().LoadSE(defaultPath + "half_se.mp3", SE_ID::HALF_SE);
	Sound::GetInstance().LoadSE(defaultPath + "stepSuccess_se.mp3", SE_ID::STEP_SUCCESS_SE);
	Sound::GetInstance().SetSEVolume(SE_ID::HIT_SE, 1.0f);
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//全リソース共通パス
	Model::GetInstance().Load(defaultPath + "Skybox/skydome.mv1", MODEL_ID::SKYBOX_MODEL);
	Model::GetInstance().Load(defaultPath + "Stage/field.mv1", MODEL_ID::STAGE_MODEL);

}
