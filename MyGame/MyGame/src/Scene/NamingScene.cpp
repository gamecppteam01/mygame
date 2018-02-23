#include "NamingScene.h"
#include"../Graphic/Sprite.h"
#include"../Math/Vector2.h"
#include"../UI/CutInText.h"
#include"../Input/InputChecker.h"
#include"../Camera/Camera.h"
#include"../Graphic/Model.h"
#include"../Define.h"
#include"../Sound/Sound.h"
#include"../DataManager/DataManager.h"


NamingScene::NamingScene()
{
	
	next_ = SceneType::SCENE_STAGESELECT;
	cameraPos_ = Vector3(0, 0, 0);
	cameraTarget_ = Vector3(0, 0, -1);
	nameState_ = NamingState::name;
	//モデルの最初のポジション
	manPos_ = Vector3(25, -13, -40);
	timer_ = 0;
	sinCount_ = 0;
	alpha_ = 0.0f;
	cursor_ = 0;
}

void NamingScene::start()
{
	light_.initialize();
	light_.changeLightTypeDir(Vector3(0, -1, 0));
	light_.setLghtSpecurColor(Color(0.1f, 0.1f, 0.1f, 1.0f));
	light_.setLightAmbientColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	light_.setLightDiffuseColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	next_ = SceneType::SCENE_STAGESELECT;
	anim_UI_ = std::make_unique<Animation_UI>(MODEL_ID::PLAYER_MODEL, manPos_);
	anim_UI_->ChangeModel(MODEL_ID::PLAYER_MODEL, MODEL_ID::PLAYER_BULLET_MODEL);

	anim_UI_->Update(1.0f / 60.0f);
}

void NamingScene::update(float deltaTime)
{
	float t = 0.0f;
	if (key_.isEnd()) {
		
		nameState_ = NamingState::select;
	}

	if (nameState_ == NamingState::select) {
		//名前が決まったら進むかどうかの確認
		if (cursor_ == 0 && InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			isEnd_ = true;
			key_.stateReset();
		}
		if (cursor_ == 1 && InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			key_.stateReset();
			DataManager::GetInstance().ResetName();
			nameState_ = NamingState::name;
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::A) ||
			InputChecker::GetInstance().GetPovTriggerDownAngle() == 90) {
			cursor_ = (cursor_ - 1 + cursorPoses.size()) % cursorPoses.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::D) ||
			InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 270)
		{
			cursor_ = (cursor_ + 1) % cursorPoses.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}

	}
	alpha_ =  MathHelper::Sin(sinCount_);
	sinCount_ = (sinCount_ + 8) % 360;
	min(alpha_, 0.0f);

	anim_UI_->Update(deltaTime);
	key_.update(deltaTime);
}

void NamingScene::draw() const
{
	//カメラの設定
	Camera::GetInstance().Position.Set(cameraPos_);
	Camera::GetInstance().Target.Set(cameraTarget_);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
	
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK, Vector2::Zero);

	if (nameState_ == NamingState::name) {

	    Sprite::GetInstance().Draw(SPRITE_ID::INPUT_NAMEFRAME_SPRITE, Vector2(550, 130));

		key_.draw(Vector2{ 500.0f,300.0f });
		CutInText::DrawMin(Vector2{ 100.0f,120.0f });

		if (key_.getState() == key_.INPUT_MEN) {
			Sprite::GetInstance().Draw(SPRITE_ID::PLAYER1_NAME_SPRITE, Vector2::Zero, 1.0f);
		}
		if (key_.getState() == key_.INPUT_WOMEN) {
			Sprite::GetInstance().Draw(SPRITE_ID::PLAYER2_NAME_SPRITE, Vector2::Zero, 1.0f);
		}

		FontManager::GetInstance().DrawTextApplyFont(655.0f, 130.0f, GetColor(255, 255, 255), FONT_ID::INPUT_SIZE_FONT, key_.getNameStr());


	}

	if (nameState_ == NamingState::select) {
		//カーソルの描画(初期左側)
		Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
		Vector2 borigin = Sprite::GetInstance().GetSize(SPRITE_ID::NAMECHECK_YES_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ cursorPoses[cursor_].first.x - borigin.x * 1.5f,cursorPoses[cursor_].first.y }, origin, std::abs(alpha_), Vector2::One, true, true);
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ cursorPoses[cursor_].first.x + borigin.x * 1.5f,cursorPoses[cursor_].first.y }, origin, std::abs(alpha_), Vector2::One, true, false);

		origin = Sprite::GetInstance().GetSize(SPRITE_ID::NAMECHECK_FRAME_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::NAMECHECK_FRAME_SPRITE, Vector2(WINDOW_WIDTH / 2 + 200.0f, WINDOW_HEIGHT / 2 - 100.0f), origin, 1.0f, Vector2::One);
		
		CutInText::DrawMin(Vector2{ (float)WINDOW_WIDTH / 2 , (float)WINDOW_HEIGHT / 2 - 160.0f });
		
		//選択肢の描画
		if (cursor_ != 0)SetDrawBright(100, 100, 100);
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::NAMECHECK_YES_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::NAMECHECK_YES_SPRITE, Vector2(WINDOW_WIDTH / 2 + 50.0f, WINDOW_HEIGHT / 2 + 200.0f), origin, 1.0f, Vector2::One);
		SetDrawBright(255, 255, 255);
		if (cursor_ != 1)SetDrawBright(100, 100, 100);
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::NAMECHECK_NO_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::NAMECHECK_NO_SPRITE, Vector2(WINDOW_WIDTH / 2 + 350.0f, WINDOW_HEIGHT / 2 + 200.0f), origin, 1.0f, Vector2::One);
		SetDrawBright(255, 255, 255);
	}

	MV1SetOpacityRate(anim_UI_->getModelHandle(), 1.0f);
	anim_UI_->Draw();

}

void NamingScene::end()
{
}
