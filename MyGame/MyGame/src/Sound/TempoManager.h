#pragma once
#include"Sound.h"
#include"../Graphic/DebugDraw.h"
#include"../Actor/Actor.h"
#include"../Method/MethodTimer.h"

class TempoManager {
public:
	TempoManager():bpm_(0) {

	}
	~TempoManager() {

	}
	void initialize() {
		bpm_ = 0;
		actors_.clear();
		justStepTimer_.Initialize();
	}
	//楽曲を設定する
	void setMusic(BGM_ID soundId,float bpm,int beat=3,int musicCount=4) {

		//サウンドリソースの読み込み
		soundHandle_=Sound::GetInstance().GetHandle(soundId);
		ChangeVolumeSoundMem(80, soundHandle_);
		//周波数の設定(44.1khz)固定値にする
		sps_ = GetFrequencySoundMem(soundHandle_);
		//SetFrequencySoundMem(44100, soundHandle_);
		//bpmを設定する
		bpm_ = bpm;
		//楽曲時間を取得する
		soundSize_ = GetSoundTotalSample(soundHandle_);

		beat_ = beat;

		sample_ = 0;
		tempoCount_ = 0.0f;
	}
	//楽曲を再生する
	void startMusic() {
		//サウンドを再生
		PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
		pause_ = false;
		sample_ = 0;
		tempoCount_ = 0.0f;

	}
	//楽曲を停止する
	void stopMusic() {
		//サウンドを停止
		StopSoundMem(soundHandle_);
	}
	//楽曲の一時停止
	void pauseMusic() {
		pause_ = true;
		StopSoundMem(soundHandle_);
	}
	//楽曲の再開
	void restartMusic() {
		PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK, FALSE);
		pause_ = false;
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

		if (getMeasureCount() % musicCount_ == 0) {
			justStepTimer_.Initialize();
			justStepTimer_.Add([&] {
				for (auto& act : actors_) {
					act.lock()->receiveNotification(Notification::Call_JustStep);
				}

			});
		}
		//1拍目以外はジャストを飛ばさない
		if (getMeasureCount() % musicCount_ != musicCount_-1)return;
		if (tempoCount_ < 0.1f) {
			justStepTimer_.Action();
		}
		//float timeSample = fmodf(sample, sps);
		//float bpmSample = timeSample / (bpm_ / 60.0f);
		//float frameSample = bpmSample / sps;
	}
	//現在拍での割合を取得する
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
	//現在何小節目かを返す
	int getMeasureCount()const {
		return getBeatCount() / beat_;
	}
	void draw()const {
		if(getBeatCount() % beat_ == 0)return;
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
	//1拍ごとの時間を返す
	float getOneBeatTime()const {
		return 60.0f / bpm_;
	}
	//何拍子かを返す
	int getBeat()const {
		return beat_;
	}
	//何小節毎で区切るか
	int getMusicCount()const {
		return musicCount_;
	}
private:
	//サウンドハンドル
	int soundHandle_;
	//bpmを指定する
	float bpm_;
	//現在のサンプル数
	int sample_;

	//1小節あたりの拍数
	int beat_{ 3 };
	//何小節区切りにするか
	int musicCount_{ 4 };
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