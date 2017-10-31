#include "LoadingScene.h"
#include"../Resource/LoadingList.h"
#include"../Graphic/EffekseerManager.h"

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {
	//�e�탊�\�[�X�̃��[�h���s��
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
	std::string defaultPath = "res/Sprite/";//�S���\�[�X���ʃp�X
	Sprite::GetInstance().Load(defaultPath + "gamestartText.png", SPRITE_ID::START_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "whitescreen.png", SPRITE_ID::WHITE_SCREEN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "blackscreen.png", SPRITE_ID::BLACK_SCREEN_SPRITE);
	Sprite::GetInstance().Load(defaultPath + "TestTitleStart.png", SPRITE_ID::TITLE_START);
	Sprite::GetInstance().Load(defaultPath + "TestTitleEnd.png", SPRITE_ID::TITLE_END);
	Sprite::GetInstance().Load(defaultPath + "TestTitleSelect.png", SPRITE_ID::TITLE_SELECT);

	Sprite::GetInstance().Load(defaultPath + "gauge.png",   SPRITE_ID::GAUGE_UI);
	Sprite::GetInstance().Load(defaultPath + "ButtonA.png", SPRITE_ID::BUTTON_A);
	Sprite::GetInstance().Load(defaultPath + "ButtonB.png", SPRITE_ID::BUTTON_B);
	Sprite::GetInstance().Load(defaultPath + "ButtonC.png", SPRITE_ID::BUTTON_C);
	Sprite::GetInstance().Load(defaultPath + "ButtonD.png", SPRITE_ID::BUTTON_D);
	Sprite::GetInstance().Load(defaultPath + "Enemy.png",   SPRITE_ID::ENEMY);
	Sprite::GetInstance().Load(defaultPath + "Player.png",  SPRITE_ID::PLAYER);
	Sprite::GetInstance().Load(defaultPath + "MiniMapScreen.png", SPRITE_ID::MINIMAP);
	
	Sprite::GetInstance().Load(defaultPath + "MiniMapScreen.png", SPRITE_ID::WARNING);
	Sprite::GetInstance().Load(defaultPath + "titlescreen.png", SPRITE_ID::TITLE_SCREEN);
	
}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//�S���\�[�X���ʃp�X
	Model::GetInstance().Load(defaultPath + "player.mv1", MODEL_ID::PLAYER_MODEL);
	Model::GetInstance().Load(defaultPath + "ghoul.mv1", MODEL_ID::ENEMY_MODEL);

}

void LoadingScene::LoadEffect()
{
	//Model�N���X�𗘗p�����G�t�F�N�g
	std::string defaultPath = "res/Sprite/Effect/";//�S���\�[�X���ʃp�X
	Model::GetInstance().Load2D(defaultPath + "circleeffect.png", MODEL_ID::EFFECT_CIRCLE_MODEL);
	Model::GetInstance().Load2D(defaultPath + "light.png", MODEL_ID::EFFECT_LIGHT_MODEL);



	//Effekseer�𗘗p�����G�t�F�N�g
	defaultPath = "res/Effekseer/";
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::SAMPLE_EFFECT, defaultPath+"laser.efk");
	EffekseerManager::GetInstance().LoadEffect(EFFECT_ID::EFFECT_TEST, defaultPath + "testeffect.efk");
}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//�S���\�[�X���ʃp�X
	FontManager::GetInstance().AddFont(FONT_ID::JAPANESE_FONT, defaultPath + "HGRGY.TTC", "HG�s����", 50);
}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//�S���\�[�X���ʃp�X
	Sound::GetInstance().LoadBGM(defaultPath + "title.mp3", BGM_ID::TITLE_BGM);

}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//�S���\�[�X���ʃp�X
	Sound::GetInstance().LoadSE(defaultPath + "check.mp3", SE_ID::CHECK_SE);
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//�S���\�[�X���ʃp�X
	Model::GetInstance().Load(defaultPath + "Skybox/skydome.mv1", MODEL_ID::SKYBOX_MODEL);
	Model::GetInstance().Load(defaultPath + "Stage/field.mv1", MODEL_ID::STAGE_MODEL);

}
