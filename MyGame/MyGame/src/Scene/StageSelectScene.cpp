#include "StageSelectScene.h"
#include"../Input/InputChecker.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/Model.h"
#include"../Define.h"
#include"../DataManager/DataManager.h"
#include "../Sound/Sound.h"
#include"../Camera/Camera.h"


//遷移先リスト
static const std::vector<std::tuple<SceneType, int, BGM_ID>> ButtonList{
	std::make_tuple(SceneType::SCENE_GAMEPLAY, 1, BGM_ID::STAGE1_BGM),
	std::make_tuple(SceneType::SCENE_GAMEPLAY, 2, BGM_ID::STAGE2_BGM),
	std::make_tuple(SceneType::SCENE_GAMEPLAY, 3, BGM_ID::STAGE3_BGM),
	std::make_tuple(SceneType::SCENE_TITLE, 1, BGM_ID::TITLE_BGM)
};

StageSelectScene::StageSelectScene() {
	next_ = SceneType::SCENE_GAMEPLAY;
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::start()
{
	light_.initialize();
	light_.changeLightTypeDir(Vector3(0.0f, 0.0f, 500.0f));
	light_.setGlobalAmbientLight(Color(0.7f, 0.7f, 0.7f, 0.7f));
	anim_UI_Mgr_.initialize();
	cursor_ = 0;
	prevCursor_ = 0;
	sinCount_ = 0;
	t = 0.0f;
	Ypos = 0.0f;
	ChangeModel();
	anim_UI_Mgr_.Updata(1.0f / 60.0f);
	cameraPos_ = Vector3(0, 0, 0);
	cameraTarget_ = Vector3(0, 0, 1);
	timer_ = 0;
	timer2_ = 0;
	fade_ = NONE;
}

void StageSelectScene::update(float deltaTime)
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) ||
		InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
		cursor_ = (cursor_ - 1 + ButtonList.size()) % ButtonList.size();
		Ypos -= 150.0f;
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		count_ = 0;
		timer_ = 0.0f;
		cameraPos_ = Vector3::Zero;
		anim_UI_Mgr_.setCenter(Vector3(-23.0f, -15.0f, 40.0f));
		fade_ = StageSelectScene::NONE;
		ChangeModel();
	}
	else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) ||
		InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180) {
		cursor_ = (cursor_ + 1) % ButtonList.size();
		Ypos += 150.0f;
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		count_ = 0;
		timer_ = 0.0f;
		cameraPos_ = Vector3::Zero;
		anim_UI_Mgr_.setCenter(Vector3(-23.0f, -15.0f, 40.0f));
		fade_ = StageSelectScene::NONE;
		ChangeModel();
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		//シーン遷移
		next_ = std::get<0>(ButtonList[cursor_]);
		Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
		DataManager::GetInstance().setStage(std::get<1>(ButtonList[cursor_]));//ステージ番号受け渡し
		isEnd_ = true;
	}
	//カーソルループ
	if (Ypos == 600.0f && InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180) Ypos = 0.0f;
	if (Ypos == -150.0f && InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) Ypos = 450.0f;
	MathHelper::Clamp(Ypos, -150.0f, 600.0f);
	t = MathHelper::Sin(sinCount_);
	sinCount_ = (sinCount_ + 8) % 360;

	ChangeBGM();

	anim_UI_Mgr_.Updata(deltaTime);

	float t;
	Vector3 pos = anim_UI_Mgr_.getCenter();
	switch (fade_)
	{
	case StageSelectScene::FADE_OUT:
		t = timer2_ / 1.0f;
		cameraPos_ = Vector3::Lerp(cameraPos_, Vector3(0, 0, -1000), t);
		pos = Vector3::Lerp(pos, Vector3(-523.0f, -15.0f, 40.0f), t);
		anim_UI_Mgr_.setCenter(pos);
		timer2_ = min(timer2_ + deltaTime, 3.0f);
		if (timer2_ >= 1.0f) fade_ = StageSelectScene::CHANGE_MODEL;
		break;
	case StageSelectScene::CHANGE_MODEL:
		ChangeModel();
		timer2_ = 0.0f;
		fade_ = StageSelectScene::FADE_IN;
		break;
	case StageSelectScene::FADE_IN:
		t = timer2_ / 1.0f;
		cameraPos_ = Vector3::Lerp(cameraPos_, Vector3(0, 0, 0), t);
		pos = Vector3::Lerp(pos, Vector3(-23.0f, -15.0f, 40.0f), t);
		anim_UI_Mgr_.setCenter(pos);
		timer2_ = min(timer2_ + deltaTime, 3.0f);
		timer_ = 0;
		if (timer2_ >= 1.5f)
			fade_ = StageSelectScene::NONE;
		break;
	case StageSelectScene::NONE:
		if (timer_ >= 5.0f) {
			if (UI_Models_[cursor_].size() == 1) return;
			count_ = (count_ + 1) % UI_Models_[cursor_].size();
			timer2_ = 0.0f;
			fade_ = FADE_OUT;
		}
		timer_ += deltaTime;
		break;
	}
}

void StageSelectScene::draw() const
{
	Camera::GetInstance().Position.Set(cameraPos_);

	Camera::GetInstance().Target.Set(cameraTarget_);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);

	Camera::GetInstance().Update();

	float cutSize = WINDOW_WIDTH / 6.0f;//ボタン軸のカット毎サイズ
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK, Vector2::Zero);

	Vector2 basePos{ cutSize*4.0f,150.0f };//1番目の位置
	float padding = 150.0f;//要素ごとの隙間

	//カーソル
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
	if (Ypos != 450)Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2(basePos - (WINDOW_WIDTH / 2 * 0.5f) + Vector2(0.0f, Ypos)), origin, std::abs(t), Vector2::One, true, true);
	Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2(basePos - (WINDOW_WIDTH / 2 * -0.5f) + Vector2(0.0f, Ypos)), origin, std::abs(t), Vector2::One, true, false);
	if (Ypos == 450)Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2(basePos - (WINDOW_WIDTH / 2 - 440.0f) + Vector2(0.0f, Ypos)), origin, std::abs(t), Vector2::One, true, true);
	//ステージ1～3
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE1_TEXT_SPRITE) / 2;
	if (cursor_ != 0)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE_1_SPRITE, basePos, origin, 1.0f, Vector2::One*0.7f);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE2_TEXT_SPRITE) / 2;
	if (cursor_ != 1)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE_2_SPRITE, Vector2{ basePos.x,basePos.y + padding }, origin, 1.0f, Vector2::One*0.7f);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE3_TEXT_SPRITE) / 2;
	if (cursor_ != 2)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE_3_SPRITE, Vector2{ basePos.x,basePos.y + padding * 2 }, origin, 1.0f, Vector2::One*0.7f);
	SetDrawBright(255, 255, 255);
	//タイトルへの遷移
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	if (cursor_ != 3)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ basePos.x + 60.0f,basePos.y + padding * 3 }, origin, 1.0f, Vector2::One*0.55f);
	SetDrawBright(255, 255, 255);

	//Model::GetInstance().Draw(MODEL_ID::BALANCEENEMY_MODEL, Vector3(0.0f, 0.0f, 20.0f));

	if (cursor_ == 3) return;
	anim_UI_Mgr_.Draw();


	//	//タイトルへの遷移
	//	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	//	if (cursor_ != 3)SetDrawBright(100, 100, 100);
	//	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,600.0f }, origin, 1.0f, Vector2::One);
	//	SetDrawBright(255, 255, 255);


		//画像描画
		//Vector2 size = Sprite::GetInstance().GetSize(SPRITE_ID::CHARACTER) / 2;
		//Vector2 size2 = Sprite::GetInstance().GetSize(SPRITE_ID::CHARACTER_NAME) / 2;
		//Sprite::GetInstance().Draw(SPRITE_ID::CHARACTER, Vector2{ WINDOW_WIDTH / 2 - 600.0f, WINDOW_HEIGHT / 2 - 100.0f }, 1.0f);
		//Sprite::GetInstance().Draw(SPRITE_ID::CHARACTER_NAME, Vector2{ WINDOW_WIDTH / 2 - 600.0f, WINDOW_HEIGHT / 2 + 50.0f}, 1.0f);
}

void StageSelectScene::end()
{
}

void StageSelectScene::ChangeBGM() {
	prevCursor_ = current_cursor_;
	current_cursor_ = cursor_;
	if (prevCursor_ == current_cursor_) return;

	Sound::GetInstance().StopBGM();
	Sound::GetInstance().PlayBGM(std::get<2>(ButtonList[cursor_]), DX_PLAYTYPE_LOOP);
}

void StageSelectScene::ChangeModel() {
	if (cursor_ == 3) return;
	anim_UI_Mgr_.UseModelAnimation(UI_Models_[cursor_][count_][0], UI_Models_[cursor_][count_][1]);
}
