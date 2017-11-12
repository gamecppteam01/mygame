#pragma once
#include"Sound.h"
#include"../Graphic/DebugDraw.h"
#include"../Actor/Actor.h"
#include"../Method/MethodTimer.h"

class TempoManager {
public:
	TempoManager():fileName_("none"),bpm_(0) {

	}
	~TempoManager() {

	}
	void initialize() {
		fileName_ = "none";
		bpm_ = 0;
		DeleteSoundMem(soundHandle_);
		actors_.clear();
		justStepTimer_.Initialize();
	}
	//楽曲を設定する
	void setMusic(const std::string& filename,float bpm) {
		//前の曲を消す
		DeleteSoundMem(soundHandle_);

		//一応名前を残す
		fileName_ = filename;
		//サウンドリソースの読み込み
		soundHandle_=LoadSoundMem(fileName_.c_str());
		//周波数の設定(44.1khz)固定値にする
		sps_ = GetFrequencySoundMem(soundHandle_);
		//SetFrequencySoundMem(44100, soundHandle_);
		//bpmを設定する
		bpm_ = bpm;
		//楽曲時間を取得する
		soundSize_ = GetSoundTotalSample(soundHandle_);

	}
	//楽曲を再生する
	void startMusic() {
		//サウンドを再生
		PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
		pause_ = false;
	}
	//楽曲を停止する
	void stopMusic() {
		//サウンドを停止
		StopSoundMem(soundHandle_);
	}
	void setActor(const ActorPtr& actor) {
		actors_.push_back(actor);
	}
	void update(float deltaTime) {
		//現在のサンプル位置を取得
		sample_ = GetCurrentPositionSoundMem(soundHandle_);
		float oneTimeSample = 60.0f/ bpm_ *sps_;//1判定毎の合計サンプル数
		float bpmSample = fmodf(sample_, oneTimeSample);//1判定毎に区切る
		tempoCount_ = bpmSample / oneTimeSample;

		if (tempoCount_ > 0.5f) {
			justStepTimer_.Initialize();
			justStepTimer_.Add([&] {
				for (auto& act : actors_) {
					act.lock()->receiveNotification(Notification::Call_CreateJustEffect);
				}
			});
		}
		if (tempoCount_ < 0.1f) {
			justStepTimer_.Action();
		}
		//float timeSample = fmodf(sample, sps);
		//float bpmSample = timeSample / (bpm_ / 60.0f);
		//float frameSample = bpmSample / sps;
	}
	//テンポを取得する
	float getTempoCount() const{
		return tempoCount_;
	}
	//拍数を返す
	int getBeatCount() const{
		float oneTimeSample = 60.0f / bpm_ *sps_;//1判定毎の合計サンプル数
		float bpmSample = sample_/ oneTimeSample;//1判定毎に区切る
		int result = max((int)bpmSample, 0);
		return result;
	}
	void draw()const {
		if(getBeatCount() % 3 == 0)return;
		DebugDraw::DebugDrawCircle(400, 400, 30, GetColor(255, 255, 255));
	}
	//再生が終了したか
	bool isEnd()const {
		//ポーズでの再生停止でなく楽曲が再生されてない場合終了
		return  !pause_&&CheckSoundMem(soundHandle_)==FALSE;
	}
	//残り再生時間
	int getRemainTime()const {
		return (soundSize_ - sample_) / sps_;
	}
private:
	//サウンドリソースのファイルパス(一応)
	std::string fileName_;
	//サウンドハンドル
	int soundHandle_;
	//bpmを指定する
	float bpm_;
	//現在のサンプル数
	int sample_;
	//0～255の範囲でテンポを取るタイマー
	float tempoCount_;
	MethodTimer justStepTimer_;
	std::vector<std::weak_ptr<Actor>> actors_;
	//楽曲サンプル数
	int soundSize_;
	//中断フラグ
	bool pause_{ false };
private:
	//サンプリング周波数(デフォルト44,1khz)
	int sps_{ 44100 };


};