#include "ResultRankManager.h"
#include"../../DataManager/DataManager.h"
#include"../../Define.h"
#include<algorithm>
#include"../../ScoreManager/NumberManager.h"
#include"../../Math/Easing.h"
#include"../../Graphic/Sprite.h"
#include"../../Sound/Sound.h"

static const float movePower{ 10.0f };
static const float lightUp{ 50.0f };
static const Vector2 defaultPos{ WINDOW_WIDTH + 100.0f, 200.0f };
static const Vector3 defaultCameraPos{ 0.0f,50.0f,-50.0f };

static const std::vector<Vector3> rankPositions{
	Vector3{ -120.0f,0.0f,0.0f },
	Vector3{ 80.0f,0.0f,0.0f },
	Vector3{ -80.0f,0.0f,0.0f },
	Vector3{ 40.0f,0.0f,0.0f },
	Vector3{ -40.0f,0.0f,0.0f },
	Vector3{ 0.0f,0.0f,0.0f }
};

static const std::vector<std::pair<bool, SPRITE_ID>> rankSprList{
	{ false,SPRITE_ID::RANK_THREE_SPRITE },
	{ false,SPRITE_ID::RANK_THREE_SPRITE },
	{ false,SPRITE_ID::RANK_THREE_SPRITE },
	{ true,SPRITE_ID::RANK_THREE_SPRITE },
	{ true,SPRITE_ID::RANK_TWO_SPRITE },
	{ true,SPRITE_ID::RANK_ONE_SPRITE }
};


static const std::vector<std::vector<SPRITE_ID>> names{
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME1_SPRITE ,SPRITE_ID::RANK_NAME5_SPRITE ,SPRITE_ID::RANK_NAME14_SPRITE,SPRITE_ID::RANK_NAME2_SPRITE },
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME4_SPRITE ,SPRITE_ID::RANK_NAME6_SPRITE ,SPRITE_ID::RANK_NAME7_SPRITE ,SPRITE_ID::RANK_NAME8_SPRITE ,SPRITE_ID::RANK_NAME3_SPRITE },
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME12_SPRITE,SPRITE_ID::RANK_NAME9_SPRITE ,SPRITE_ID::RANK_NAME11_SPRITE,SPRITE_ID::RANK_NAME10_SPRITE,SPRITE_ID::RANK_NAME13_SPRITE }
};

ResultRankManager::ResultRankManager()
{
}

void ResultRankManager::init()
{
	animType_ = 0;
	currentTarget_ = 0;
	lerpTimer_ = 0.0f;
	isLast_ = false;
	state_ = State::Start;
	settingLight();
	soundVolume_ = 1.0f;
	camera_.init();

	characters_.clear();

	auto datas = DataManager::GetInstance().getData();
	stage_ = DataManager::GetInstance().getStage();
	Vector3 position{ -80.0f,0.0f,0.0f };

	int i = rankPositions.size() - datas.size();
	incSize_ = i;
	for (auto& d : datas) {
		Matrix id{ Matrix::Identity };
		std::shared_ptr<ResultModelDrawer> rmd = std::make_shared<ResultModelDrawer>();


		characters_.push_back(std::make_tuple(d, position, id, rmd, defaultPos));
		std::get<3>(characters_.back())->setModel(std::get<0>(characters_.back()).manModel_, std::get<0>(characters_.back()).womanModel_);
		std::get<3>(characters_.back())->setAnim(0);
		std::get<3>(characters_.back())->lastAnim();
		
		position += Vector3{ 40.0f,0.0f,0.0f };
	}

	std::sort(characters_.begin(), characters_.end(), [](auto& c1, auto& c2) {return std::get<0>(c1).score_ < std::get<0>(c2).score_; });

	for (auto& c : characters_) {
		std::get<1>(c) = rankPositions[i];
		i++;

	}
}

void ResultRankManager::update(float deltaTime)
{
	switch (state_)
	{
	case ResultRankManager::State::Start:
		Start(deltaTime);
		break;
	case ResultRankManager::State::MoveLeft:
		MoveLeft(deltaTime);
		break;
	case ResultRankManager::State::CameraMove:
		CameraMove(deltaTime);
		break;
	case ResultRankManager::State::Light:
		Light(deltaTime);
		break;
	case ResultRankManager::State::CameraReturn:
		CameraReturn(deltaTime);
		break;

	case ResultRankManager::State::Animation:
		Animation(deltaTime);
		break;
	case ResultRankManager::State::EndLight:
		EndLight(deltaTime);
		break;
	case ResultRankManager::State::MoveDown:
		MoveDown(deltaTime);
		break;
	case ResultRankManager::State::Next: {
		Next(deltaTime);
		break;
	}
	case ResultRankManager::State::End:
		End(deltaTime);
		break;
	default:
		break;
	}
	if (state_ != ResultRankManager::State::Animation) {
		if (Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE)) {
			soundVolume_ -= deltaTime;
			Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, soundVolume_);
			if (soundVolume_ <= 0.0f) {
				Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
			}
		}
	}
	camera_.update(deltaTime);

	for (auto& c : characters_) {
		std::get<3>(c)->update(1.0f);
	}
}

void ResultRankManager::draw() const
{
	camera_.draw();
	int count = -1;
	for (auto& c : characters_) {
		count++;

		std::get<3>(c)->draw(std::get<1>(c), std::get<2>(c));
	}
	count = -1;
	for (auto& c : characters_) {
		count++;

		if (currentTarget_ < count)continue;

		float scl = 0.3f;
		float sprx = Sprite::GetInstance().GetSize(SPRITE_ID::RANK_ONE_SPRITE).x*scl;
		Vector2 pos = std::get<4>(c);
		//NumberManager::GetInstance().DrawNumberTexture(SPRITE_ID::NUMBER, pos, std::get<0>(c).score_, Vector2(64, 64), Vector2(0.5f, 0.5f));
		if (rankSprList.at(count + incSize_).first)Sprite::GetInstance().Draw(rankSprList.at(count + incSize_).second, pos, Vector2::Zero, Vector2::One*scl);
		auto spr = names.at(stage_ - 1).at(std::get<0>(c).playerNumber_ - 1);
		Sprite::GetInstance().Draw(spr, pos + Vector2{ sprx ,0.0f }, Vector2::Zero, Vector2::One*0.4f);

	}


}

void ResultRankManager::end()
{
	lightHandle_.deleteLightHandleAll();

}

bool ResultRankManager::isEnd() const
{
	return state_ == State::End;
}

void ResultRankManager::Start(float deltaTime)
{
	currentTarget_ = 0;
	lerpTimer_ = 0.0f;
	changeState(State::MoveLeft);
}

void ResultRankManager::MoveLeft(float deltaTime)
{
	float time = 0.6f;
	lerpTimer_ += deltaTime;
	bool isChange = false;
	if (lerpTimer_ >= time) {
		lerpTimer_ = time;
		isChange = true;
	}
	float leftPos = Easing::EaseOutQuint(lerpTimer_, defaultPos.x, 50.0f - defaultPos.x, time);
	std::get<4>(characters_[currentTarget_]).x = leftPos;
	
	if (isChange) {
		changeState(State::Light);
	}


}

void ResultRankManager::CameraMove(float deltaTime)
{
	if (camera_.isEnd()) {
		if (currentTarget_ <= characters_.size() - 3) {//3位以下
			animType_ = 0;
		}
		else if (currentTarget_ == characters_.size() - 2) {//2位
			animType_ = 2;
		}
		else {//1位
			animType_ = 3;
			isLast_ = true;
			changeState(State::Animation,true);
			return;
		}


		changeState(State::Animation);
	}
}

void ResultRankManager::CameraReturn(float deltaTime)
{
	if (camera_.isEnd()) {

		changeState(State::MoveDown);
	}

}

void ResultRankManager::Light(float deltaTime)
{
	//if (!camera_.isEnd())return;

	changeState(State::CameraMove);
}

void ResultRankManager::Animation(float deltaTime)
{
	if (isLast_) {
		timer_ += deltaTime;
		if (timer_ >= std::get<3>(characters_[currentTarget_])->getMaxAnimTime()) {
			changeState(State::MoveDown);
			return;
		}
	}
	if (std::get<3>(characters_[currentTarget_])->isEnd())changeState(State::EndLight);
}

void ResultRankManager::EndLight(float deltaTime)
{	
	changeState(State::CameraReturn);
}

void ResultRankManager::MoveDown(float deltaTime)
{
	float spriteYSize = 80.0f;
	float downPos = defaultPos.y + (characters_.size() - currentTarget_-1)*spriteYSize;
	std::get<4>(characters_[currentTarget_]) += Vector2{ 0.0f,movePower };
	if (std::get<4>(characters_[currentTarget_]).y > downPos) {
		std::get<4>(characters_[currentTarget_]).y = min(std::get<4>(characters_[currentTarget_]).y, downPos);
		if (isLast_) changeState(State::End);
		else changeState(State::Next);
	}

}

void ResultRankManager::Next(float deltaTime)
{
	currentTarget_++;
	if (currentTarget_ >= characters_.size()) {
		changeState(State::End);
	}
	else {
		changeState(State::MoveLeft);
	}
}

void ResultRankManager::End(float deltaTime)
{
}

void ResultRankManager::changeState(State state,bool isLoop)
{

	state_ = state;

	switch (state_)
	{
	case ResultRankManager::State::Start:
		break;
	case ResultRankManager::State::MoveLeft:
		lerpTimer_ = 0.0f;
		break;
	case ResultRankManager::State::CameraMove:
		camera_.start(std::get<1>(characters_[currentTarget_]) + Vector3{ -30.0f,0.0f,40.0f }, Vector3{0.0f,-70.0f,0.0f}, ResultEasingType::EaseOutQuad, ResultEasingType::EaseOutQuad, ResultEasingType::EaseInCirc);
		break;
	case ResultRankManager::State::CameraReturn:
		camera_.start(defaultCameraPos, Vector3{ 0.0f,-30.0f,0.0f });
		break;
	case ResultRankManager::State::Light:
		lightHandle_.setLightEnableHandle("Spot", true);
		lightHandle_.setLightPositionHandle("Spot", std::get<1>(characters_[currentTarget_])+Vector3::Up*lightUp);
		//camera_.zoomIn();
		break;
	case ResultRankManager::State::Animation:
		std::get<3>(characters_[currentTarget_])->setAnim(animType_, isLoop);
		timer_ = 0.0f;
		Sound::GetInstance().PlaySE(SE_ID::CHEER_SE);
		soundVolume_ = 1.0f;
		Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE,soundVolume_);
		break;
	case ResultRankManager::State::EndLight:
		lightHandle_.setLightEnableHandle("Spot", false);
		//camera_.zoomOut();
		break;
	case ResultRankManager::State::MoveDown:
		break;
	case ResultRankManager::State::Next:
		break;
	case ResultRankManager::State::End:
		break;
	default:
		break;
	}
}

//ライトの設定関数

inline void ResultRankManager::settingLight() {
	//標準ライトの設定
	standardLight_.initialize();
	standardLight_.changeLightTypeDir(Vector3(0.0f, -1.0f, 0.0f));
	standardLight_.setLightAmbientColor(Color(0.1f, 0.1f, 0.1f, 0.1f));
	standardLight_.setLghtSpecurColor(Color(0.5f, 0.5f, 0.5f, 0.5f));
	standardLight_.setLightDiffuseColor(Color(0.5f, 0.5f, 0.5f, 0.5f));

	//ライトハンドルの設定
	lightHandle_.setUsePixelLighting(true);
	lightHandle_.createSpotLightHandle("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 500.0f, 0.75f, 0.003f, 0.0f);
	lightHandle_.setLightAmbientColorHandle("Spot", Color(0.0f, 0.0f, 0.0f, 0.0f));
	lightHandle_.setLightDiffuseColorHandle("Spot", Color(0.7f, 0.7f, 0.2f, 1.0f));
	lightHandle_.setLightSpecuarColorHandle("Spot", Color(1.0f, 1.0f, 1.0f, 1.0f));
	//グローバルアンビエントの設定
	standardLight_.setGlobalAmbientLight(Color(0.0f, 0.0f, 0.0f, 0.0f));

	lightHandle_.setLightEnableHandle("Spot", false);
	lightHandle_.setLightPositionHandle("Spot", camera_.currentTarget()+Vector3::Up*lightUp);

}
