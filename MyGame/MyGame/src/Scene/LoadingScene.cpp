#include "LoadingScene.h"
#include"../Resource/LoadingList.h"

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_GAMEPLAY;
}

void LoadingScene::start() {
	//�e�탊�\�[�X�̃��[�h���s��
	LoadSprite();
	LoadModel();
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

}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//�S���\�[�X���ʃp�X
	Model::GetInstance().Load(defaultPath + "player.mv1", MODEL_ID::PLAYER_MODEL);

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
	Model::GetInstance().Load(defaultPath + "Stage/SampleStage_Castle.mv1", MODEL_ID::STAGE_MODEL);

}
