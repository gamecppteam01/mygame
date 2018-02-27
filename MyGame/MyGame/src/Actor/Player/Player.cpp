#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Input/InputChecker.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"
#include"../../Graphic/Sprite.h"
#include"../Body/BoundingCapsule.h"
#include"PlayerBullet.h"
#include"../ActorGroup.h"
#include"../../Camera/OverLookingCamera.h"
#include"../EffectActor/UniqueEffectActor/TrackingEffectActor.h"
#include"../../Effect/CircleEffect.h"
#include"../Dummy/BetweenPositionActor.h"
#include"../../Input/DualShock4Manager.h"
#include"../../Judge/JudgeDefine.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../Graphic/FontManager.h"
#include"../../Math/MathHelper.h"
#include"../../Sound/TempoManager.h"
#include"../../Graphic/EffekseerManager.h"
#include"../../Math/Random.h"
#include"../Judge/Judgement_SpotLight/Judgement_SpotLight.h"
#include"ShootCollider.h"
#include"../../UI/UI.h"
#include"../../UI/SpecifiedStepManager.h"
#include"PlayerBuffManager.h"

//moveからidleに移行する際のinput確認数カウント
static const int inputCheckCount = 4;
//男と女の距離
static const Vector3 bulletDistance{ 0.0f,0.0f,4.0f };
//回転力の基本係数
static const float defaultTurnPower = 1.0f;
static const float boundPower = 15.0f;
static const float downTime = 2.0f;
//移動速度
static const float movePower = 0.5f;
//ステップ回数によるよろけのチェック周期
static const int defStepCount = 3;

//スピンの回転範囲
static const float spinPower = 6.0f;

//男->女でアニメーションを変換
static const std::map<Player_Animation, PlayerBullet::PlayerBullet_Animation> animConvList{
	{ Player_Animation::Move_Forward,PlayerBullet::PlayerBullet_Animation::Move_Forward },
	{ Player_Animation::Idle,PlayerBullet::PlayerBullet_Animation::Idle },
	{ Player_Animation::Quarter,PlayerBullet::PlayerBullet_Animation::Quarter },
	{ Player_Animation::Attack,PlayerBullet::PlayerBullet_Animation::Attack },
	{ Player_Animation::Down,PlayerBullet::PlayerBullet_Animation::Down },
	{ Player_Animation::KnockBack,PlayerBullet::PlayerBullet_Animation::KnockBack },
	{ Player_Animation::Shoot,PlayerBullet::PlayerBullet_Animation::Shoot },
	{ Player_Animation::ShootEnd,PlayerBullet::PlayerBullet_Animation::ShootEnd },
	{ Player_Animation::Step_Left,PlayerBullet::PlayerBullet_Animation::Step_Left },
	{ Player_Animation::Half,PlayerBullet::PlayerBullet_Animation::Half },
	{ Player_Animation::Turn,PlayerBullet::PlayerBullet_Animation::Turn },
	{ Player_Animation::Reversal,PlayerBullet::PlayerBullet_Animation::Reversal },
	{ Player_Animation::Stumble,PlayerBullet::PlayerBullet_Animation::Stumble }
};

static const std::map<int, Player_Animation> toAnimList{
	{ 0,Player_Animation::Move_Forward },//例外
	{ 1,Player_Animation::Quarter },//クォーター変換
	{ 2,Player_Animation::Half },//ハーフ変換
	{ 3,Player_Animation::Turn },//ターン変換
	{ 4,Player_Animation::Shoot }//スピン変換
}; 
Player::Player(IWorld* world, const std::string& name, const Vector3& position, int playerNumber) :
	Actor(world, name, position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),
		Matrix::Identity, 20.0f, 3.0f)), upVelocity_(0.0f), velocity_(Vector3::Zero), gravity_(0.0f), animation_(),
	state_(Player_State::Idle), prevState_(Player_State::Idle), defaultPosition_(position), centerPosition_(position),
	bulletVelocity_(Vector3::Zero), turnPower_(1.0f), bound_(Vector3::Zero), playerNumber_(playerNumber),
	gyroCheck_(), musicScore_(), stepEffect_(world),turnEffect_(world), appear_stepUI_(world, this), spinEffect_(world),
	quaterEffect_(world),halfEffect_(world), isZoomEnd_(true), checkFunc_([&] {return ComboChecker::checkCombo(comboChecker_, stepAnimScoreList_.at(nextStep_).first, world_); }),
	lightTimeUI_()
{
	buffManager_ = std::make_shared<PlayerBuffManager>();
	createBullet();
	world_->addActor(ActorGroup::PLAYER_BULLET, bullet_);

	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL));
	bullet_->changeAnimation(PlayerBullet::PlayerBullet_Animation::Move_Forward);
	initialize();

	//各種更新関数を設定する
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {idle_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Move] = [this](float deltaTime) {move_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step] = [this](float deltaTime) {step_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step_Success] = [this](float deltaTime) {stepSuccess_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Attack] = [this](float deltaTime) {attack_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Shoot] = [this](float deltaTime) {shoot_Update(deltaTime); };
	playerUpdateFunc_[Player_State::ShootEnd] = [this](float deltaTime) {shootend_Update(deltaTime); };
	playerUpdateFunc_[Player_State::KnockBack] = [this](float deltaTime) {knockback_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Down] = [this](float deltaTime) {down_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Stumble] = [this](float deltaTime) {stumble_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Reversal] = [this](float deltaTime) {reversal_Update(deltaTime); };

	//各種状態変更関数を設定する
	playerToNextModeFunc_[Player_State::Idle] = [this]() {to_IdleMode(); };
	playerToNextModeFunc_[Player_State::Move] = [this]() {to_MoveMode(); };
	playerToNextModeFunc_[Player_State::Step] = [this]() {to_StepMode(); };
	playerToNextModeFunc_[Player_State::Step_Success] = [this]() {to_StepSuccessMode(); };
	playerToNextModeFunc_[Player_State::Attack] = [this]() {to_AttackMode(); };
	playerToNextModeFunc_[Player_State::Shoot] = [this]() {to_ShootMode(); };
	playerToNextModeFunc_[Player_State::ShootEnd] = [this]() {to_ShootEndMode(); };
	playerToNextModeFunc_[Player_State::KnockBack] = [this]() {to_KnockBackMode(); };
	playerToNextModeFunc_[Player_State::Down] = [this]() {to_DownMode(); };
	playerToNextModeFunc_[Player_State::Stumble] = [this]() {to_StumbleMode(); };
	playerToNextModeFunc_[Player_State::Reversal] = [this]() {to_ReversalMode(); };

	playerEndModeFunc_[Player_State::Idle] = [this]() {		end_IdleMode(); };
	playerEndModeFunc_[Player_State::Move] = [this]() {		end_MoveMode(); };
	playerEndModeFunc_[Player_State::Step] = [this]() {		end_StepMode(); };
	playerEndModeFunc_[Player_State::Step_Success] = [this]() {		end_StepSuccessMode(); };
	playerEndModeFunc_[Player_State::Attack] = [this]() {	end_AttackMode(); };
	playerEndModeFunc_[Player_State::Shoot] = [this]() {	end_ShootMode(); };
	playerEndModeFunc_[Player_State::ShootEnd] = [this]() {	end_ShootEndMode(); };
	playerEndModeFunc_[Player_State::KnockBack] = [this]() {end_KnockBackMode(); };
	playerEndModeFunc_[Player_State::Down] = [this]() {		end_DownMode(); };
	playerEndModeFunc_[Player_State::Stumble] = [this]() {		end_StumbleMode(); };
	playerEndModeFunc_[Player_State::Reversal] = [this]() {		end_ReversalMode(); };

	musicScore_.SetWorld(world);
	musicScore_.SetSize(Vector2{ 250.0f,20.0f });
	musicScore_.SetMeasure(3.f);

	appear_stepUI_.SetWorld(world);
}

Player::~Player()
{
}

void Player::setCheckStepTask(std::list<Player_Animation> checkstep)
{
	checkstep_.setInputLimit(checkstep);
}

void Player::setIncrementStepTask(std::list<Player_Animation> checkstep)
{
	checkstep_.setInputRelease(checkstep);

}

void Player::addVelocity(const Vector3 & velocity)
{
	velocity_ += velocity;
}

void Player::hitEnemy(const std::string& hitName, const Vector3& velocity)
{
	if (!isCanStumble()&&!isAttack()&&state_!=Player_State::Down&&state_ != Player_State::Reversal)return;
	if (comboType_ == ComboChecker::ComboType::Combo_Burst)return;//バーストコンボ成立中はひるまない
	bound_ += velocity;

	//攻撃状態ならひるまない
	if (isAttack()) {
		if (state_ == Player_State::Attack)change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward);
		return;
	}
	else if (state_ == Player_State::Down|| state_ == Player_State::Reversal) {
		return;
	}
	
	if (buffManager_->hit()) {//シールドが切れて無ければひるまない
		return;
	}
	stumbleDirection_ = mathStumbleDirection(Vector2(-velocity.x, -velocity.z));
	//stumbleDirection_ = -velocity;
	stumbleResurrectTime_ = 0.5f;
	change_State_and_Anim(Player_State::Stumble, Player_Animation::Stumble);
}

float Player::getPlayerScoreRate() const
{
	return world_->getScoreManager().GetCharacterScoreRate(playerNumber_);
}

void Player::startStepAnim()
{
	animation_.ChangeAnim((int)Player_Animation::Quarter, 0.0f, 1.0f, false);
	bullet_->changeAnimation(animConvList.at(Player_Animation::Quarter), 0.0f, 1.0f, false);
}

void Player::stepAnimUpdate(float deltaTime)
{
	animation_.Update(1.0f);
	bullet_->stepAnimUpdate(deltaTime);

}

bool Player::isStepAnimEnd()
{
	return animation_.IsAnimEnd();
}

void Player::endStepAnim()
{
	animation_.ChangeAnim((int)Player_Animation::Move_Forward);
	bullet_->changeAnimation(animConvList.at(Player_Animation::Move_Forward));

}

void Player::initCheckStep()
{
	checkstep_.initialize();
}

LightTimeDrawUI * Player::getLightTimeDrawUIPtr() 
{
	return &lightTimeUI_;
}

void Player::createBullet()
{
	bullet_ = std::make_shared<PlayerBullet>(world_, position_, this);
}

void Player::initialize()
{
	isFirst_ = true;
	isZoomEnd_ = true;
	position_ = centerPosition_ + bulletDistance;
	gravity_ = 0.0f;
	state_ = Player_State::Idle;
	prevState_ = state_;
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
	changeAnimation(Player_Animation::Move_Forward);

	lightTimeUI_.init();

	buffManager_->setPlayer(this);

	turnPower_ = 1.0f;
	bullet_->initialize();
	checkstep_.initialize();
	//女の移動と回転の操作権を得る
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

	*bulletPosition_ = centerPosition_ - bulletDistance;

	gyroCheck_.initialize();
	musicScore_.Initialize();
	appear_stepUI_.Initialize();
	comboChecker_.clear();
	comboType_ = ComboChecker::ComboType::Combo_None;
	comboTimer_ = 0.0f;
	puComboCount_ = 0;
	comboResetTimer_ = 0;
	isChangeBurstMode_ = false;
}

void Player::onPause()
{
	restartSEList_.clear();

	if (Sound::GetInstance().IsPlaySE(SE_ID::HIT_SE)) {
		Sound::GetInstance().StopSE(SE_ID::HIT_SE);
		restartSEList_.push_back(SE_ID::HIT_SE);
	}
	if (Sound::GetInstance().IsPlaySE(SE_ID::HALF_SE)) {
		Sound::GetInstance().StopSE(SE_ID::HALF_SE);
		restartSEList_.push_back(SE_ID::HALF_SE);
	}
	if (Sound::GetInstance().IsPlaySE(SE_ID::STEP_SUCCESS_SE)) {
		Sound::GetInstance().StopSE(SE_ID::STEP_SUCCESS_SE);
		restartSEList_.push_back(SE_ID::STEP_SUCCESS_SE);
	}



}

void Player::onRestart()
{
	for (auto& r : restartSEList_) {
		Sound::GetInstance().PlaySE(r, DX_PLAYTYPE_BACK, FALSE);
	}
	restartSEList_.clear();
}

void Player::onMessage(EventMessage message, void * param)
{
}

void Player::onUpdate(float deltaTime)
{
	if (comboType_ == ComboChecker::ComboType::Combo_PointUp) {
		if (!EffekseerManager::GetInstance().isPlayEffect3D(puEffectID_)) {
			puEffectID_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, position_, Vector3::Zero, Vector3::One*0.5f);
			EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::POINT_UP_EFFECT, puEffectID_, &position_);
		}
	}
	//ジャスト範囲外かつコンボ制限を超過したら
	if (!((world_->getCanChangedTempoManager().getMeasureCount() % world_->getCanChangedTempoManager().getMusicCount()) == world_->getCanChangedTempoManager().getMusicCount() - 1)) {
		if (comboResetTimer_ <= 0&&comboType_==ComboChecker::ComboType::Combo_None) {
			comboChecker_.clear();//コンボをリセット
			//auto stepComboMgr = world_->findUI("StepComboManager");
			//if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_End);
			auto stepdrawer = world_->findUI("ComboDrawer");
			if (stepdrawer != nullptr)stepdrawer->Notify(Notification::Call_Combo_End);

		}
	}
	//バーストコンボ中は無条件ステップ
	if (comboType_ == ComboChecker::ComboType::Combo_Burst) {
		musicScore_.setNotice(true);
		comboTimer_ -= deltaTime;
		if (comboTimer_ <= 0.0f) {
			musicScore_.setNotice(false);
			comboChecker_.clear();
			comboType_ = ComboChecker::ComboType::Combo_None;//時間になったらコンボを終了する
			//auto stepComboMgr = world_->findUI("StepComboManager");
			//if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_End);
			auto stepdrawer = world_->findUI("ComboDrawer");
			if (stepdrawer != nullptr)stepdrawer->Notify(Notification::Call_Combo_End);
		}
	}
	else {
		auto ptr = std::dynamic_pointer_cast<Judgement_SpotLight>(world_->findActor("SpotLight"));
		if (ptr != nullptr) {
			musicScore_.setNotice(ptr->getIsNotice(playerNumber_));
		}
	}
	if (isFirst_)isFirst_ = false;
	else playerUpdateFunc_[state_](deltaTime);

	animation_.Update(MathHelper::Sign(deltaTime));

	//今フレームの更新を適用
	centerPosition_ += velocity_;

	if (state_ != Player_State::Shoot&&state_ != Player_State::Attack) {
		position_ = bulletDistance*rotation_ + centerPosition_;
		*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
	}
	velocity_ -= velocity_*0.5f;
	correctPosition();

	//女を更新する
	if (isCanTracking())bulletUpdate(deltaTime);

	//float tempo = std::abs(world_->getCanChangedTempoManager().getTempoCount() - 0.5f);
	//float pow = 2.0f;
	//effectSize_ = 1.0f-(std::powf(tempo, pow)*2.0f*pow);


	float tempo = world_->getCanChangedTempoManager().getTempoCount();
	float beat = (world_->getCanChangedTempoManager().getBeatCount() % 3);
	effectSize_[0] = 3.0f - (tempo + beat);
	effectSize_[0] = effectSize_[0] / 3.f;

	musicScore_.Update(deltaTime);
	buffManager_->update(deltaTime);
	lightTimeUI_.update(deltaTime);
}

void Player::onDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));

	//DrawFormatStringToHandle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), FontManager::GetInstance().GetFontHandle(FONT_ID::JAPANESE_FONT), std::to_string(nextStep_).c_str());



	//world_->setLateDraw([this] {
	//	
	//	Vector2 origin = Vector2(0.5f, 0.5f);
	//	float beat = (world_->getCanChangedTempoManager().getBeatCount() % 3);
	//	if (isJustTiming()) {
	//		SetDrawBright(200, 30, 100);
	//	}
	//	float size = 1.0f;
	//	float tempo = world_->getCanChangedTempoManager().getTempoCount();
	//	if (tempo <= 0.3f) {
	//		size = 1.0f+ (0.3f - tempo);
	//	}
	//	Model::GetInstance().Draw2D(MODEL_ID::JUST_CIRCLE_MODEL, centerPosition_, 0, 24.0f*size , origin, 0.0f, 1.0f);
	//	Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, centerPosition_, 0, 22.0f*size, origin, 0.0f, 0.7f);
	//	Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, centerPosition_, 0, 10.0f*size, origin, 0.0f, 0.7f);
	//	SetDrawBright(0, 255, 255);
	//	Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, centerPosition_, 0, effectSize_[0] * 32.0f*size, origin, 0.0f, 1.0f);
	//	SetDrawBright(255, 255, 255);
	//	//3連ジャストサークル
	//	/*
	//	//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 0)SetDrawBright(200, 0, 0);
	//	SetDrawBright(200, 0, 0);
	//	Vector2 origin = Vector2(0.5f, 0.5f);
	//	Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, effectSize_[0]*64.0f, origin, 0.0f, 1.0f);
	//	SetDrawBright(255, 255, 255);
	//	//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)SetDrawBright(200, 0, 0);
	//	Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, effectSize_[1]*64.0f, origin, 0.0f, 1.0f);
	//	//SetDrawBright(255, 255, 255);
	//	//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 1)SetDrawBright(200, 0, 0);
	//	Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, effectSize_[2]*64.0f, origin, 0.0f, 1.0f);
	//	SetDrawBright(255, 255, 255); 
	//	*/
	//}
	//);


	if (state_ == Player_State::Step_Success || state_ == Player_State::Shoot || state_ == Player_State::Attack)return;

	world_->setLateDraw([this] {
		//musicScore_.Draw(Vector2{ WINDOW_WIDTH / 2.f,WINDOW_HEIGHT/2.f });
		float size=musicScore_.Draw(centerPosition_ + Vector3{ 0.0f,-8.0f,0.0f }, rotation_.Up());
		lightTimeUI_.draw_player(centerPosition_ + Vector3{ 0.0f,-8.0f,0.0f }, rotation_.Up(), size);
		//DrawFormatString(400,300,GetColor(255,255,255),"%d",(int)comboType_);//デバッグ表示

		////デバッグ表示
		//int i = 0;
		//for (const auto& c : comboChecker_) {
		//	switch (c)
		//	{
		//	case Player_Animation::Quarter: {
		//		DrawFormatString(50, 400 + 50 * i, GetColor(255, 255, 255), "Quarter");
		//		break;
		//	}
		//	case Player_Animation::Half: {
		//		DrawFormatString(50, 400 + 50 * i, GetColor(255, 255, 255), "Half");
		//		break;
		//	}
		//	case Player_Animation::Turn: {
		//		DrawFormatString(50, 400 + 50 * i, GetColor(255, 255, 255), "Turn");
		//		break;
		//	}
		//	case Player_Animation::Shoot: {
		//		DrawFormatString(50, 400 + 50 * i, GetColor(255, 255, 255), "Spin");
		//		break;
		//	}
		//	default:
		//		break;
		//	}
		//	i++;
		//}

	}
	, false);

	appear_stepUI_.Draw(centerPosition_ + Vector3{ 0.0f,25.0f,0.0f });
}

void Player::onShadowDraw() const
{
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));

}

void Player::onCollide(Actor & other)
{
	if ((other.getName() == "Enemy" || other.getName() == "EnemyBullet")) {
		Sound::GetInstance().PlaySE(SE_ID::HIT_SE);
	}

}
void Player::onCollideResult()
{
	bound_.y = 0.0f;
	Vector3 bound = bound_.Normalize()*boundPower;
	bound.y = 0.0f;
	bulletVelocity_ += bound;
	//シュート時でなければプレイヤー自身も発射する
	if (state_ != Player_State::Shoot)velocity_ += bound;

	bound_ = Vector3::Zero;

	if (state_ == Player_State::Shoot)return;

	position_ = bulletDistance*rotation_ + centerPosition_;
	*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
}

void Player::JustStep()
{
	//ステップ関係中じゃなければカウントをマイナス
	if (state_ != Player_State::Step&&
		state_ != Player_State::Step_Success&&
		state_ != Player_State::Attack&&
		state_ != Player_State::Shoot&&
		state_ != Player_State::ShootEnd
		) {
		//時間が来たら
		comboResetTimer_--;
	}
	//ステップ周期が来たら
	stepCount_++;
	//姿勢のチェックが必要なら
	if (!isRequiredCheckPosture())return;
	if (stepCount_ >= defStepCount) {
		stepCount_ = 0;
		//バランスを取れてるかをチェック
		//if (DualShock4Manager::GetInstance().GetAngle3D().z <= 45.0f) {
		//	downTime_ = 2.0f;
		//	change_State_and_Anim(Player_State::Down, Player_Animation::Down, 0.0f, 1.0f, false);
		//}
	}
}

void Player::CreateJustEffect()
{
	//createCircleEffect();
}

bool Player::field(Vector3 & result)
{
	if (!world_->getField()->isInField(centerPosition_)) {
		centerPosition_ = world_->getField()->CorrectPosition(centerPosition_);
		if (state_ != Player_State::Shoot) {
			position_ = bulletDistance*rotation_ + centerPosition_;
			*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
		}
	}
	Vector3 hit1;
	Vector3 hit2;
	//中心をそのままcenterに入れよう
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), *bulletPosition_ + body_->points(0), *bulletPosition_ + body_->points(1), bullet_->body_->radius(), (VECTOR*)&hit1, (VECTOR*)&hit2))
	{
		//本体と弾の中心を返す
		result = (hit1 + hit2)*0.5f + ((body_->points(0)));

		return true;
	}
	return false;
}

void Player::gravityUpdate(float deltaTime)
{
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, upVelocity_ + gravity_, 0.0f);
	velocity_ += jumpVector;

}

void Player::correctPosition()
{
	Vector3 result;
	if (field(result)) {
		centerPosition_ = result;
	}
	Vector3 start = centerPosition_ + body_->points(1);
	Vector3 end = start + Vector3::Down*(body_->radius() + 1.0f);
	if (world_->getField()->getMesh().collide_line(start, end)) {
		gravity_ = 0.0f;
	}

}

bool Player::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop, float blend)
{
	if (state_ == state)return false;
	if (!checkstep_(animID))return false;

	changeAnimation(animID, animFrame, animSpeed, isLoop, blend);
	bullet_->changeAnimation(animConvList.at(animID), animFrame, animSpeed, isLoop, blend);
	change_State(state);

	return true;
}

bool Player::change_State(Player_State state)
{
	//状態が変わらないなら失敗
	if (state_ == state)return false;

	//状態の終了処理を行う
	playerEndModeFunc_[state_]();
	//状態を更新
	prevState_ = state_;
	state_ = state;
	//状態変更を行う
	playerToNextModeFunc_[state_]();
	//更新成功
	return true;
}

void Player::idle_Update(float deltaTime)
{
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) > ignoreSlope || std::abs(move.y) > ignoreSlope) {
		/*if (*/change_State_and_Anim(Player_State::Move, Player_Animation::Move_Forward);//)playerUpdateFunc_[state_](deltaTime);
		return;
	}
	//if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
	//	if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot, 0.0f, 1.0f, false))playerUpdateFunc_[state_](deltaTime);
	//	return;
	//}
	if (isChangeStep()) {
		if (isJustTiming()) {
			change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left);//)playerUpdateFunc_[state_](deltaTime);
		}
		else {
			std::vector<Vector2> stumbleList{
				Vector2::Right,
				Vector2::Left,
				Vector2::Up,
				Vector2::Down
			};
			stumbleDirection_ = stumbleList[Random::GetInstance().Range(0, 3)];
			
			//成功通知
			auto stepUI = world_->findUI("StepUI");
			if (stepUI != nullptr)stepUI->Notify(Notification::Call_StepFailed);
			change_State_and_Anim(Player_State::Stumble, Player_Animation::Stumble);//)playerUpdateFunc_[state_](deltaTime);
		
		}
		return;
	}
	upVelocity_ -= upVelocity_*0.5f;

	gravityUpdate(deltaTime);

}

void Player::move_Update(float deltaTime)
{
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) < ignoreSlope && std::abs(move.y) < ignoreSlope) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;

	//if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
	//	if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot, 0.0f, 1.0f, false))playerUpdateFunc_[state_](deltaTime);
	//	return;
	//}

	if (isChangeStep()) {
		if (isJustTiming()) {
			if (change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left))playerUpdateFunc_[state_](deltaTime);
		}
		else {
			std::vector<Vector2> stumbleList{
				Vector2::Right,
				Vector2::Left,
				Vector2::Up,
				Vector2::Down
			};
			stumbleDirection_ = stumbleList[Random::GetInstance().Range(0, 3)];

			//成功通知
			auto stepUI = world_->findUI("StepUI");
			if (stepUI != nullptr)stepUI->Notify(Notification::Call_StepFailed);
			if (change_State_and_Anim(Player_State::Stumble, Player_Animation::Stumble))playerUpdateFunc_[state_](deltaTime);

		}
		return;
	}

	upVelocity_ -= upVelocity_*0.5f;

	velocity_ += framevelocity;

	gravityUpdate(deltaTime);

}

void Player::step_Update(float deltaTime)
{
	if (!isChangeStep()) {
		if (nextStep_ != 0) {
			//ダンスが成立してたら対応したアニメーションを再生(実行順序の関係でここではStateの変更のみ行い、内部で実行されるto_StepSuccessにてアニメーションを更新する)
			if (change_State(Player_State::Step_Success))playerUpdateFunc_[state_](deltaTime);
			return;
		}
		else {
			//成功通知
			auto stepUI = world_->findUI("StepUI");
			if(stepUI!=nullptr)stepUI->Notify(Notification::Call_StepFailed);
			
			if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
			return;
		}
	}

	gyroCheck_.update();
	Vector2 rotate = gyroCheck_.getRotate();
	if (abs(rotate.y) >= 270.0f) {
		//1回転成立
		successStep_ = 3;
	}
	else if (rotate.y >= 160.0f)successStep_ = 2;
	else if (rotate.y >= 90.0f&&successStep_ != 2)successStep_ = 1;

	if (std::abs(gyroCheck_.getAngle()) >= 300.0f) {
		successStep_ = 4;
		nextStep_ = successStep_;
		//現在制限されているステップじゃなかったら
		auto locklist = checkstep_.getLockList_();
		if (std::find(locklist.begin(), locklist.end(), toAnimList.at(nextStep_)) == locklist.end()) {
			//成立UIを表示
			appear_stepUI_.Notify(nextStep_);
		}
		gyroCheck_.initAngle();
		Sound::GetInstance().PlaySE(SE_ID::STEP_SUCCESS_SE);//音成立
	}
	if (DualShock4Manager::GetInstance().GetAngle3D().z > 45.0f&&DualShock4Manager::GetInstance().GetAngle3D().z <= 100.0f) {
		gyroCheck_.initRotate();
		if (nextStep_ != successStep_)Sound::GetInstance().PlaySE(SE_ID::STEP_SUCCESS_SE);//音成立
		nextStep_ = successStep_;
		//現在制限されているステップじゃなかったら
		auto locklist = checkstep_.getLockList_();
		if (std::find(locklist.begin(), locklist.end(), toAnimList.at(nextStep_)) == locklist.end()) {
			//成立UIを表示
			appear_stepUI_.Notify(nextStep_);
		}
	}

}

void Player::stepSuccess_Update(float deltaTime)
{
	timeCount_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (timeCount_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward, 0.0f, 1.0f, true))playerUpdateFunc_[state_](deltaTime);
		return;
	}
}

void Player::attack_Update(float deltaTime)
{
	timeCount_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (timeCount_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	stepAttack(deltaTime);

	shootAngle_ += 5.0f;

	Vector3 baseRotatePos = bulletDistance;
	position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));
	//回転を更新
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	Vector3 rotatePos = -bulletDistance;
	*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));


}

void Player::shoot_Update(float deltaTime)
{
	velocity_ = Vector3::Zero;
	shootAngle_ += 3.5f;
	Vector3 baseRotatePos = bulletDistance + bulletDistance*(1 - (MathHelper::Abs(180.f - shootAngle_) / 180.0f)) * spinPower;//離れ具合
	position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));//男の位置更新
	//回転を更新
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -2.0f*turnPower_);

	Vector3 rotatePos = -bulletDistance + -bulletDistance*(1 - (MathHelper::Abs(180.f - shootAngle_) / 180.0f))*spinPower;
	*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));
	//回転を更新
	//*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -2.0f*turnPower_);

	if (shootAngle_ >= 360.0f) {
		//if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		if (change_State(Player_State::ShootEnd))playerUpdateFunc_[state_](deltaTime);
		return;

	}
}

void Player::shootend_Update(float deltaTime)
{
	if (animation_.IsAnimEnd())
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
}

void Player::knockback_Update(float deltaTime)
{
}

void Player::down_Update(float deltaTime)
{
	timeCount_ += deltaTime;

	if (timeCount_ >= downTime_) {
		if (change_State_and_Anim(Player_State::Reversal, Player_Animation::Reversal, 0.0f, 1.0f, false))playerUpdateFunc_[state_](deltaTime);
	}
}

void Player::turn_Update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}

}

void Player::stumble_Update(float deltaTime)
{
	timeCount_ += deltaTime;
	//よろけ時間がダウン時間に到達したら転倒
	if (timeCount_ >= fallTime) {
		//転倒処理を書く
		downTime_ = downTime;//ダウン時間設定
		if (change_State_and_Anim(Player_State::Down, Player_Animation::Down, 0.f, 1.f, false,0.0f))playerUpdateFunc_[state_](deltaTime);

	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	//よろけ修正方向を向いたら
	if (Vector3::Angle(Vector3(stumbleDirection_.x, 0.0f, stumbleDirection_.y), Vector3(move.x, 0.0f, move.y)) <= 20.0f&&move.Length() >= 0.2f) {
		stumbleRegistTimer_ += deltaTime;
		if (stumbleRegistTimer_ >= stumbleResurrectTime_) {
			if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
			return;
		}
	}
	else {
		stumbleRegistTimer_ = 0.0f;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;

	upVelocity_ -= upVelocity_*0.5f;

	velocity_ += framevelocity;

	gravityUpdate(deltaTime);

}

void Player::reversal_Update(float deltaTime)
{
	timeCount_ -= deltaTime;

	if (timeCount_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward, 0.0f, 1.0f, true))playerUpdateFunc_[state_](deltaTime);
	}

}

void Player::to_IdleMode()
{

}

void Player::to_MoveMode()
{

}
void Player::to_StepMode()
{
	//EffekseerManager::GetInstance().StopEffect3D(effectID_);

	//effectID_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::STEP_STANDBY_INPUT2_EFFECT, centerPosition_);

	//ジャスト判定タイミングならスコア加算フラグを有効にする
	isJustStep_ = isJustTiming();

	gyroCheck_.initialize();
	successStep_ = 0;
	nextStep_ = 0;
	appear_stepUI_.Notify(0);
	stepEffect_.start();
}

void Player::to_StepSuccessMode()
{
	bool isLast = checkstep_.isLast();
	if (!checkstep_(stepAnimScoreList_.at(nextStep_).first)) {
		change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward, 0.0f, 1.0f, true, 0.0f);
		return;
	}
	world_->getCamera()->ZoomIn(0, 0);

	int key = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::STEP_SUCCESS_EFFECT, centerPosition_, Vector3::Zero, Vector3::One*10.0f);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::STEP_SUCCESS_EFFECT, key, &position_);
	//スコア加算を呼び出す(ステップ開始時点でジャスト判定に合っていなかったら加算されない)
	bool isChangeTypeNone = false;//この回でnone状態に遷移したかどうか
	bool isChangePUMode = false;
	if (isJustStep_) {
		float scoreRate = 1.0f;//コンボ用のスコアレート

		//ポイントアップコンボ中はスコアレート1.2倍
		if (comboType_ == ComboChecker::ComboType::Combo_PointUp) {

			scoreRate = 1.2f;
			puComboCount_--;
			//回数が終わったらコンボ終了
			if (puComboCount_ <= 0) {
				comboChecker_.clear();
				comboType_ = ComboChecker::ComboType::Combo_None;
				//auto stepComboMgr = world_->findUI("StepComboManager");
				//if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Combo_End);
				auto stepdrawer = world_->findUI("ComboDrawer");
				if (stepdrawer != nullptr)stepdrawer->Notify(Notification::Call_Combo_End);

				if (EffekseerManager::GetInstance().isPlayEffect3D(puEffectID_)) {
					EffekseerManager::GetInstance().StopEffect3D(puEffectID_);
				}
				isChangeTypeNone = true;
			}
		}
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnimScoreList_.at(nextStep_).second*scoreRate);
	}
	isChangeBurstMode_ = false;
	//今コンボ中じゃないかつこの回でポイントアップが終わってなかったらコンボ追加
	if (checkstep_.isEndCheck()&& !isLast && comboType_ == ComboChecker::ComboType::Combo_None && !isChangeTypeNone) {
		comboResetTimer_ = 2;//コンボリセットまでの猶予は2回
		comboType_ = checkFunc_();
		if (comboType_ == ComboChecker::ComboType::Combo_Burst) {

			//auto stepComboMgr = world_->findUI("StepComboManager");
			//if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Success_Combo_Burst);
			auto cd = world_->findUI("ComboDrawer");
			if (cd != nullptr)cd->Notify(Notification::Call_Success_Combo_Burst);

			isChangeBurstMode_ = true;
			comboType_ = ComboChecker::ComboType::Combo_None;//一時的にNoneにしてステップ終了時にバーストに遷移

			comboTimer_ = 8.0f;//バーストコンボが成立したら8秒間無敵
		}
		if (comboType_ == ComboChecker::ComboType::Combo_PointUp) {
			puComboCount_ = 4;//ポイントアップコンボが成立したら4回スコア上昇
			if (!EffekseerManager::GetInstance().isPlayEffect3D(puEffectID_)) {
				puEffectID_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT);
				EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::POINT_UP_EFFECT, puEffectID_, &position_);
			}
			//auto stepComboMgr = world_->findUI("StepComboManager");
			//if (stepComboMgr != nullptr)stepComboMgr->Notify(Notification::Call_Success_Combo_PointUp);
			auto cd = world_->findUI("ComboDrawer");
			if (cd != nullptr)cd->Notify(Notification::Call_Success_Combo_PointUp);
			isChangePUMode = true;
		}
	}
	changeAnimation(stepAnimScoreList_.at(nextStep_).first, 0.0f, 1.0f, false);
	bullet_->changeAnimation(animConvList.at(stepAnimScoreList_.at(nextStep_).first), 0.0f, 1.0f, false);

	//対応したアニメーションの終了時間を取得する
	timeCount_ = animation_.GetAnimMaxTime((int)stepAnimScoreList_.at(nextStep_).first);

	//成功通知
	auto stepUI = world_->findUI("StepUI");
	if (stepUI != nullptr)stepUI->Notify(Notification::Call_StepSuccess, (void*)&nextStep_);

	if (nextStep_ == 1) {
		quaterEffect_.start();
	}
	if (nextStep_ == 2) {
		//Sound::GetInstance().PlaySE(SE_ID::HALF_SE);
		halfEffect_.start();
		change_State_and_Anim(Player_State::Attack, stepAnimScoreList_.at(nextStep_).first);
		return;
	}
	if (nextStep_ == 3) {
		turnEffect_.start();
	}
	if (nextStep_ == 4) {
		spinEffect_.start();
		change_State_and_Anim(Player_State::Shoot, stepAnimScoreList_.at(nextStep_).first);
		return;
	}

}

void Player::to_AttackMode()
{
	world_->getCamera()->ZoomIn(1, 1);

	shootAngle_ = 0.0f;

	changeAnimation(stepAnimScoreList_.at(nextStep_).first);

	//対応したアニメーションの終了時間を取得する
	timeCount_ = animation_.GetAnimMaxTime((int)stepAnimScoreList_.at(nextStep_).first);

	std::list<ActorPtr> enemys;
	world_->findActors("Enemy", enemys);

	if (enemys.empty()) {
		attackTarget_ = shared_from_this();
		return;
	}
	attackTarget_ = enemys.front();
	for (auto& e : enemys) {
		if (Vector3::Distance(centerPosition_, attackTarget_->position()) > Vector3::Distance(centerPosition_, e->position())) {
			attackTarget_ = e;
		}
	}

	attackPower_ = 20;
}

void Player::to_ShootMode()
{
	world_->getCamera()->ZoomIn(0, 0);

	world_->addActor(ActorGroup::PLAYER, std::make_shared<ShootCollider>(this));
	shootAngle_ = 0.0f;
	Vector3 shootVector = *bulletPosition_ - position_;
	shootVector = shootVector.Normalize();
	bulletVelocity_ = shootVector*(turnPower_*defaultTurnPower);

	attackPower_ = 20;
}

void Player::to_ShootEndMode()
{
}

void Player::to_KnockBackMode()
{

}

void Player::to_DownMode()
{
	timeCount_ = 0.0f;
}

void Player::to_TurnMode()
{
}

void Player::to_StumbleMode()
{
	if (prevState_ == Player_State::Step) {
		//成功通知
		auto stepUI = world_->findUI("StepUI");
		if (stepUI != nullptr)stepUI->Notify(Notification::Call_StepFailed);

	}
	timeCount_ = 0.0f;
	stumbleRegistTimer_ = 0.0f;
}

void Player::to_ReversalMode()
{
	timeCount_ = animation_.GetAnimMaxTime((int)Player_Animation::Reversal);

}

void Player::end_IdleMode()
{
}

void Player::end_MoveMode()
{
}

void Player::end_StepMode()
{
	EffekseerManager::GetInstance().StopEffect3D(effectID_);
	stepEffect_.end();
}

void Player::end_StepSuccessMode()
{
	if (nextStep_ != 2 && nextStep_ != 4) {
		auto ssUIManager = std::static_pointer_cast<SpecifiedStepManager>(world_->findUI("SpecifiedStepManager"));
		if (ssUIManager != nullptr)ssUIManager->stepMatching(nextStep_);
	}
	//if (!checkstep_(stepAnimScoreList_.at(nextStep_).first))return;

	isZoomEnd_ = false;
	world_->getCamera()->setZoomEndFunc([&] {isZoomEnd_ = true; });

	world_->getCamera()->ZoomOut();
	//バーストへの遷移が成立してたら遷移する
	if (isChangeBurstMode_) {
		isChangeBurstMode_ = false;
		comboType_ = ComboChecker::ComboType::Combo_Burst;//一時的にNoneにしてステップ終了時にバーストに遷移
		comboTimer_ = 8.0f;//バーストコンボが成立したら8秒間無敵
	}
	turnEffect_.end();
	quaterEffect_.end();
	spinEffect_.end();
	halfEffect_.end();
}

void Player::end_AttackMode()
{
	isZoomEnd_ = false;
	world_->getCamera()->setZoomEndFunc([&] {isZoomEnd_ = true; });

	world_->getCamera()->ZoomOut();
	auto ssUIManager = std::static_pointer_cast<SpecifiedStepManager>(world_->findUI("SpecifiedStepManager"));
	if (ssUIManager != nullptr)ssUIManager->stepMatching(2);

	attackPower_ = 5;

}

void Player::end_ShootMode()
{
	isZoomEnd_ = false;
	world_->getCamera()->setZoomEndFunc([&] {isZoomEnd_ = true; });

	world_->getCamera()->ZoomOut();
	auto sc=world_->findActor("ShootCenter"); 
	if (sc != nullptr)sc->dead();

	auto ssUIManager = std::static_pointer_cast<SpecifiedStepManager>(world_->findUI("SpecifiedStepManager"));
	if (ssUIManager != nullptr)ssUIManager->stepMatching(4);

	attackPower_ = 5;
	buffManager_->shield();

}

void Player::end_ShootEndMode()
{
}

void Player::end_KnockBackMode()
{
}

void Player::end_DownMode()
{
}

void Player::end_TurnMode()
{
}

void Player::end_StumbleMode()
{
}

void Player::end_ReversalMode()
{
}

void Player::stepAttack(float deltaTime)
{
	centerPosition_ += (attackTarget_->position() - centerPosition_).Normalize() *2.f;
}

void Player::changeAnimation(Player_Animation animID, float animFrame, float animSpeed, bool isLoop, float blend) {
	animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop, blend);
}

bool Player::isChangeStep() const
{
	return  {
		(
			InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::A) ||
			InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::B) ||
			InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::X) ||
			InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::Y)
			)
		&&
		InputChecker::GetInstance().GetPovAngle() != -1
	};
}
bool Player::isCanStumble() const
{
	if (state_ == Player_State::Idle || state_ == Player_State::Move || state_ == Player_State::Step||state_==Player_State::Stumble)return true;
	//if (state_ == Player_State::Step_Success && (nextStep_ != 2 && nextStep_ != 4))return true;
	return false;
}

bool Player::isAttack()
{
	return state_ == Player_State::Attack || state_ == Player_State::Shoot;
}

bool Player::isRequiredCheckPosture() const
{
	return state_ == Player_State::Idle || state_ == Player_State::Move;
}

bool Player::isCanTracking() const
{
	//発射時以外は追従する
	return state_ != Player_State::Shoot;
}

void Player::bulletUpdate(float deltaTime)
{
	*bulletPosition_ = centerPosition_ + (-bulletDistance*rotation_);

	*bulletRotation_ = rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f);
	//*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

}

void Player::createCircleEffect()
{
	std::shared_ptr<CircleEffect> circleEffect = std::make_shared<CircleEffect>(40.0f, justEffectStartTime);
	world_->addActor(ActorGroup::EFFECT, std::make_shared<TrackingEffectActor>(world_, "CircleEffect", centerPosition_, circleEffect, shared_from_this()));
}

Vector2 Player::getSticktoMove()
{
	Vector2 result = InputChecker::GetInstance().Stick();
	result.y = -result.y;
	return result;

}

Vector2 Player::mathStumbleDirection(const Vector2 & stumbleDirection)
{

	Vector2 result = Vector2::Zero;

	Vector2 base = Vector2::One;
	Vector2 target = stumbleDirection;

	base = base.Normalize();
	target = target.Normalize();

	float cross = Vector2::Cross(base, target);
	float dot = Vector2::Dot(base, target);
	dot = MathHelper::ACos(dot);


	//右が+
	if (cross >= 0) {
		dot *= -1;
	}
	if (dot >= 0 && dot <= 90) {
		result = Vector2::Left;
	}
	if (dot >= 90 && dot <= 180) {
		result = Vector2::Up;
	}
	if (dot <= 0 && dot >= -90) {
		result = Vector2::Down;
	}
	if (dot <= -90 && dot >= -180) {
		result = Vector2::Right;
	}
	return result;
}

bool Player::isJustTiming() const
{
	//return world_->getCanChangedTempoManager().getBeatCount() % 3 == 0;
	if (musicScore_.getNotice())return true;
	return musicScore_.isJust();// (world_->getCanChangedTempoManager().getMeasureCount() % world_->getCanChangedTempoManager().getMusicCount()) >= world_->getCanChangedTempoManager().getMusicCount() - 2;
}
