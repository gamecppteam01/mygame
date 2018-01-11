#include "ResultScoreDraw.h"
#include"../../DataManager/DataManager.h"
#include"../../Define.h"
#include"../../Graphic/FontManager.h"
#include"../../ScoreManager/NumberManager.h"
#include"../../Graphic/Sprite.h"
#include"../../Graphic/Model.h"
#include"../../Graphic/DxlibGraphic.h"
#include<algorithm>

static const Vector2 basePos{ 0.0f,300.0f };
ResultScoreDraw::ResultScoreDraw(): animation_(){
}

ResultScoreDraw::~ResultScoreDraw()
{
}

void ResultScoreDraw::init()
{
	dataList_.clear();
	auto dt = DataManager::GetInstance().getData();
	dt.sort([](ScoreData& s1, ScoreData& s2) {return s1.score_ < s2.score_; });
	dataList_.assign(dt.begin(), dt.end());

	drawCount_ = 0;
	lerpTimer_ = 0.0f;

	another_position_ = Vector2::Zero;

	float x = 0.0f;
	float y = 0.0f;

	count = 0.0f;

	state_ = ResultScoreDraw::Start;

	for (int i = 0; i < dataList_.size(); i++) {
		PlayerList.push_back(std::make_pair(dataList_.at(i), Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)));
	}
	std::sort(PlayerList.begin(), PlayerList.end(),
		[](auto &x, auto&y)
	{return x.first.rank_ > y.first.rank_; });
	curent_key = 0;

	animation_.initialize();
}

void ResultScoreDraw::update(float deltaTime)
{
	if (curent_key >= PlayerList.size())return;

	switch (state_)
	{
	case ResultScoreDraw::Start:
		state_ = ResultScoreDraw::Move1;
		break;
	case ResultScoreDraw::Move1:
		x = MathHelper::Lerp(WINDOW_WIDTH, 32.0f, lerpTimer_);

		PlayerList[curent_key].second = basePos + Vector2{ x,0.0f };

		lerpTimer_ += deltaTime * 0.5;
		lerpTimer_ = min(lerpTimer_, 1.0);

		if (lerpTimer_ >= 1.0f) {
			state_ = ResultScoreDraw::Animation;
		}
		break;
	case ResultScoreDraw::Animation:	
		if (PlayerList[curent_key].first.playerNumber_ <= 1) {
			animation_.set(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL), Model::GetInstance().GetHandle(MODEL_ID::PLAYER_BULLET_MODEL));
		}
		else {
			animation_.set(Model::GetInstance().GetHandle(MODEL_ID::BALANCEENEMY_MODEL), Model::GetInstance().GetHandle(MODEL_ID::BALANCEENEMY_BULLET_MODEL));
		}
		if (curent_key >= PlayerList.size() - 2) {
			//アニメーション
			animation_.update(deltaTime);
			animation_.animation();
			if (animation_.end()) {
				lerpTimer_ = 0.0f;
				another_position_ = PlayerList[curent_key].second;
				state_ = ResultScoreDraw::Move2;
			}
		}
		else {
			lerpTimer_ = 0.0f;
			another_position_ = PlayerList[curent_key].second;
			count += deltaTime * 0.75;
			count = min(count, 1);
			if (count >= 1) {
				state_ = ResultScoreDraw::Move2;
			}
		}
		break;
	case ResultScoreDraw::Move2:
		y = MathHelper::Lerp(0.0f, 350.0f - 150.0f * curent_key, lerpTimer_);

		PlayerList[curent_key].second = another_position_ + Vector2{ 0.0,y };

		lerpTimer_ += deltaTime * 0.5;
		lerpTimer_ = min(lerpTimer_, 1.0);

		if (lerpTimer_ >= 1.0f) {
			state_ = ResultScoreDraw::End;
		}
		break;
	case ResultScoreDraw::End:
		lerpTimer_ = 0.0f;
		count = 0.0f;
		curent_key++;
		state_ = ResultScoreDraw::Start;
		break;
	default:
		break;
	}
	
}

void ResultScoreDraw::draw() const
{
	//DrawSprite3D(Vector3(0.0f, 0.0f, 0.0f), 128.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::RESULT_STAGE), 255, 255, 255, 255, 0.0f, 0.0f, 0.0f);
	int key_ = curent_key;
	key_ = min(curent_key, PlayerList.size() - 1);
	for (int i = 0; i < key_ + 1; i++) {
		NumberManager::GetInstance().DrawNumberTexture(SPRITE_ID::NUMBER, PlayerList[i].second, i - PlayerList.size(), Vector2(64, 64), Vector2(0.5f, 0.5f));
		switch (PlayerList.at(i).first.playerNumber_)
		{
		case 1:
			Sprite::GetInstance().Draw(SPRITE_ID::PLAYER_SCORE, Vector2{ PlayerList[i].second.x + 128.0f, PlayerList[i].second.y - 32.0f });
			break;
		case 2:
			Sprite::GetInstance().Draw(SPRITE_ID::ENEMY1_SCORE, Vector2{ PlayerList[i].second.x + 128.0f, PlayerList[i].second.y - 32.0f });
			break;
		case 3:
			Sprite::GetInstance().Draw(SPRITE_ID::ENEMY2_SCORE, Vector2{ PlayerList[i].second.x + 128.0f, PlayerList[i].second.y - 32.0f });
			break;
		case 4:
			Sprite::GetInstance().Draw(SPRITE_ID::ENEMY3_SCORE, Vector2{ PlayerList[i].second.x + 128.0f, PlayerList[i].second.y - 32.0f });
			break;
		default:
			break;
		}
	}
	if (curent_key >= PlayerList.size() - 2 && state_==ResultScoreDraw::Animation) {
		animation_.draw(Vector3(0.0f,0.0f,0.0f));
	}
}

bool ResultScoreDraw::end() const
{
	if (curent_key >= PlayerList.size())return true;
	return false;
}
